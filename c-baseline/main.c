#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEAP_TYPE int

#include "heap.h"

int compare_ints(int a, int b) {
    return a < b;
}

int main(int argc, char **argv) {
    int heap_max = 10000;
    struct heap *heap = create_heap(heap_max, &compare_ints);

    int time = 0;
    int total = 5000000;

    clock_t t;
    t = clock();

    // simulation
    for (int idx = 0; idx < total; idx++) {
        if (heap->size >= heap_max) {
            time = pop_heap(heap);
        }

        int diff = idx % 2 == 0 ? 2 :
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
