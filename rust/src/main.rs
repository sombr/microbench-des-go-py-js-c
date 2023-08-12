use std::env;
use std::time::Instant;

#[derive(Debug)]
struct Heap<T: Copy + std::cmp::PartialOrd + std::default::Default> {
    size: usize,
    capacity: usize,
    data: Vec<T>
}

impl<T: Copy + std::cmp::PartialOrd + std::default::Default> Heap<T> {
    pub fn new(capacity: usize) -> Heap<T> {
        let mut data = Vec::with_capacity(capacity+1);
        for _ in 0..capacity+1 {
            data.push(Default::default());
        }
        Heap{
            size: 0,
            capacity: capacity,
            data: data
        }
    }

    pub fn len(&self) -> usize {
        return self.size;
    }

    fn parent_idx(&self, pos: usize) -> usize {
        return pos / 2;
    }

    fn left_idx(&self, pos: usize) -> usize {
        return pos * 2;
    }

    fn right_idx(&self, pos: usize) -> usize {
        return pos * 2 + 1;
    }

    fn is_leaf(&self, pos: usize) -> bool {
        return self.left_idx(pos) > self.size;
    }

    fn swap(&mut self, a: usize, b: usize) {
        (self.data[a], self.data[b]) = (self.data[b], self.data[a]);
    }

    pub fn push(&mut self, item: T) {
        if self.size >= self.capacity {
            panic!("pushing into a full container");
        }

        self.size += 1;
        let mut cur = self.size;

        self.data[cur] = item;
        while cur > 1 && self.data[cur] < self.data[ self.parent_idx(cur) ] {
            self.swap( cur, self.parent_idx(cur) );
            cur = self.parent_idx(cur);
        }
    }

    fn percolate(&mut self, pos: usize) {
        if self.is_leaf(pos) {
            return;
        }

        let cur = self.data.get(pos).unwrap();
        let left = self.data.get( self.left_idx(pos) );
        let right = self.data.get( self.right_idx(pos) );

        if left.map_or(false, |l| l < cur) || right.map_or(false, |r| r < cur) {
            if right.is_none() || left.unwrap() < right.unwrap() {
                self.swap(pos, self.left_idx(pos));
                self.percolate( self.left_idx(pos));
            } else {
                self.swap(pos, self.right_idx(pos));
                self.percolate( self.right_idx(pos));
            }
        }
    }

    pub fn pop(&mut self) -> T {
        if self.size < 1 {
            panic!("empty heap");
        }

        let res = self.data[1];
        self.data[1] = self.data[ self.size ];
        self.size -= 1;
        self.percolate(1);

        return res;
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let heap_max: usize = args[1].parse().unwrap();

    let mut sim_time: u32 = 0;
    let total: u32 = args[2].parse().unwrap();

    let mut heap: Heap<u32> = Heap::new(heap_max);

    let start = Instant::now();

    for idx in 0..total {
        if heap.len() >= heap_max {
            sim_time = heap.pop();
        }

        let diff = if idx % 2 == 0 { 2 } else {
                   if idx % 3 == 0 { 5 } else { 20 } };

        heap.push(sim_time + diff);
    }

    while heap.len() > 0 {
        sim_time = heap.pop();
    }

    let duration = start.elapsed();

    println!("RUST simulation result {}, runtime: {} ms", sim_time, (duration.as_micros() as f64) / 1000.0);
}
