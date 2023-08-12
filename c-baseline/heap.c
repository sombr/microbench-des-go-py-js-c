#include "heap.h"

struct heap* create_heap(int capacity, HEAP_COMPARATOR) {
    struct heap *heap = (struct heap*) malloc( sizeof(struct heap) );
    heap->size = 0;
    heap->capacity = capacity;
    heap->comparator = comparator;
    heap->data = (HEAP_TYPE*) malloc( (capacity + 1) * sizeof(HEAP_TYPE) );

    return heap;
}

void destroy_heap(struct heap *heap) {
    free(heap->data);
    free(heap);
}

int _heap_parent_idx(int pos) {
    return pos / 2;
}

int _heap_left_idx(int pos) {
    return pos * 2;
}

int _heap_right_idx(int pos) {
    return pos * 2 + 1;
}

int _heap_is_leaf(struct heap *heap, int pos) {
    return _heap_left_idx(pos) > heap->size;
}

void _heap_swap(struct heap *heap, int a, int b) {
    HEAP_TYPE tmp = heap->data[a];
    heap->data[a] = heap->data[b];
    heap->data[b] = tmp;
}

void push_heap(struct heap *heap, HEAP_TYPE item) {
    if (heap->size >= heap->capacity) {
        printf("pushing into a full container\n");
        exit(1);
    }

    heap->size += 1;
    int cur = heap->size;

    heap->data[cur] = item;
    while ( cur > 1 && (heap->comparator)(heap->data[cur], heap->data[ _heap_parent_idx(cur) ]) ) {
        _heap_swap(heap, cur, _heap_parent_idx(cur));
        cur = _heap_parent_idx(cur);
    }
}

HEAP_TYPE peek_heap(struct heap *heap) {
    if (heap->size < 1) {
        printf("empty heap\n");
        exit(1);
    }

    return heap->data[1];
}

void _heap_percolate(struct heap *heap, int pos) {
    if (_heap_is_leaf(heap, pos))
        return;

    HEAP_TYPE cur = heap->data[pos];
    HEAP_TYPE left = heap->data[ _heap_left_idx(pos) ];
    HEAP_TYPE right = heap->data[ _heap_right_idx(pos) ];

    if (
        (
            (heap->comparator)(left, cur) &&
            _heap_left_idx(pos) <= heap->size
        ) ||
        (
            (heap->comparator)(right, cur) &&
            _heap_right_idx(pos) <= heap->size
        )
       ) {
        if ( (heap->comparator)(left, right) || _heap_right_idx(pos) > heap->size ) {
            _heap_swap(heap, pos, _heap_left_idx(pos));
            _heap_percolate(heap, _heap_left_idx(pos));
        } else {
            _heap_swap(heap, pos, _heap_right_idx(pos));
            _heap_percolate(heap, _heap_right_idx(pos));
        }
    }
}

HEAP_TYPE pop_heap(struct heap *heap) {
    if (heap->size < 1) {
        printf("popping from an empty heap\n");
        exit(1);
    }

    HEAP_TYPE res = heap->data[1];
    heap->data[1] = heap->data[ heap->size ];
    heap->size -= 1;
    _heap_percolate(heap, 1);

    return res;
}

