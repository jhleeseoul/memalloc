#include "metric.h"
#include "memalloc.h"
#include "memalloc_internal.h"
#include <time.h>

extern block_t* get_free_list_head();

double measure_avg_alloc_time(size_t size, int iterations) {
    clock_t start = clock();

    void** ptrs = (void**)my_malloc(sizeof(void*) * iterations);
    for (int i = 0; i < iterations; ++i) {
        ptrs[i] = my_malloc(size);
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    // 해제
    for (int i = 0; i < iterations; ++i) {
        if (ptrs[i]) my_free(ptrs[i]);
    }
    my_free(ptrs);

    return elapsed / iterations;
}

double calculate_external_fragmentation() {
    block_t* curr = get_free_list_head();
    size_t total_free = 0;
    size_t largest = 0;

    while (curr) {
        if (curr->free) {
            total_free += curr->size;
            if (curr->size > largest)
                largest = curr->size;
        }
        curr = curr->next;
    }

    if (total_free == 0) return 0.0;
    return 1.0 - ((double)largest / total_free);
}

double calculate_heap_utilization() {
    block_t* curr = get_free_list_head();
    size_t used = 0;

    while (curr) {
        if (!curr->free)
            used += curr->size;
        curr = curr->next;
    }

    return (double)used / HEAP_SIZE;
}
