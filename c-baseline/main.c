#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define HEAP_TYPE uint32_t

#include "heap.h"

int compare_ints(uint32_t a, uint32_t b) {
    return a < b;
}

int main(int argc, char **argv) {
    uint32_t heap_max = 10000;
    struct heap *heap = create_heap(heap_max, &compare_ints);

    uint32_t time = 0;
    uint32_t total = 5000000;

    clock_t t;
    t = clock();

    // simulation
    for (uint32_t idx = 0; idx < total; idx++) {
        if (heap->size >= heap_max) {
            time = pop_heap(heap);
        }

        uint32_t diff = idx % 2 == 0 ? 2 :
                   idx % 3 == 0 ? 5 : 20;

        push_heap(heap, time + diff);
    }

    while (heap->size > 0) {
        time = pop_heap(heap);
    }

    t = clock() - t;
    double time_taken = ((double)t)/(CLOCKS_PER_SEC/1000); // in seconds

    destroy_heap(heap);

    printf("C simulation result: %d, runtime: %.2f ms\n", time, time_taken);
}
