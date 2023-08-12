
class IntHeap {
    constructor(capacity) {
        this.capacity = capacity;
        this.size = 0;
        this.data = new Int32Array(capacity+1);
    }

    length() {
        return this.size;
    }

    #parent_idx(pos) {
        return (pos / 2) | 0; // wtf javascript, why don't you have sane typecasting.
    }

    #left_idx(pos) {
        return pos * 2;
    }

    #right_idx(pos) {
        return pos * 2 + 1;
    }

    #is_leaf(pos) {
        return this.#left_idx(pos) > this.size;
    }

    #swap(a, b) {
        const tmp = this.data[a];
        this.data[a] = this.data[b];
        this.data[b] = tmp;
    }

    push(item) {
        if (this.size >= this.capacity) {
            throw "pushing into a full container";
        }

        this.size += 1;
        let cur = this.size;

        this.data[cur] = item;
        while ( cur > 1 && this.data[cur] < this.data[ this.#parent_idx(cur) ] ) {
            this.#swap(cur, this.#parent_idx(cur));
            cur = this.#parent_idx(cur);
        }
    }

    peek() {
        if (this.size < 1) {
            throw "empty heap";
        }

        return this.data[1];
    }

    #percolate(pos) {
        if (this.#is_leaf(pos)) {
            return;
        }

        let cur = this.data[pos];
        let left = this.data[ this.#left_idx(pos) ];
        let right = this.#right_idx(pos) <= this.size ? this.data[ this.#right_idx(pos) ] : null;

        if ( (left < cur) || (right != null && right < cur) ) {
            if ( right == null || left < right ) {
                this.#swap(pos, this.#left_idx(pos));
                this.#percolate(this.#left_idx(pos));
            } else {
                this.#swap(pos, this.#right_idx(pos));
                this.#percolate(this.#right_idx(pos));
            }
        }
    }

    pop() {
        if (this.size < 1) {
            throw "empty heap";
        }

        let res = this.data[1];
        this.data[1] = this.data[ this.size ];
        this.size -= 1;

        this.#percolate(1);

        return res;
    }
}

function main() {
    let heap_max = 10000;

    let sim_time = 0;
    let total = 5000000;

    let heap = new IntHeap(heap_max);

    const start = performance.now();

    for (let idx = 0; idx < total; idx += 1) {
        if (heap.length() >= heap_max) {
            sim_time = heap.pop();
        }

        diff = idx % 2 == 0 ? 2:
               idx % 3 == 0 ? 5 : 20;

        heap.push(sim_time + diff);
    }

    while (heap.length() > 0) {
        sim_time = heap.pop();
    }

    const elapsed = performance.now() - start;

    console.log("JS simulation result:", sim_time, ", runtime:", elapsed.toFixed(2), "ms");
}

main();
