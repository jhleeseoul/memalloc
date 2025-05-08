#ifndef MEMALLOC_H
#define MEMALLOC_H

#include <stddef.h>

#define HEAP_SIZE (1024 * 1024)  // 1MB 힙 크기

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    NEXT_FIT
} alloc_policy_t;

void* my_malloc(size_t size);
void my_free(void* ptr);

void init_heap();
void set_alloc_policy(alloc_policy_t policy);

#endif
