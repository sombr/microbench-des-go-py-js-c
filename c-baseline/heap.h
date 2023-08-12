#include <stdlib.h>
#include <stdio.h>

#ifndef HEAP_TYPE
#define HEAP_TYPE int
#endif

#define HEAP_COMPARATOR int (*comparator)(HEAP_TYPE a, HEAP_TYPE b)

struct heap {
    int size;
    int capacity;
    HEAP_COMPARATOR; // returns true when a < b
    HEAP_TYPE *data;
};

struct heap* create_heap(int capacity, HEAP_COMPARATOR);
void destroy_heap(struct heap *heap);

void push_heap(struct heap *heap, HEAP_TYPE item);
HEAP_TYPE peek_heap(struct heap *heap);
HEAP_TYPE pop_heap(struct heap *heap);
