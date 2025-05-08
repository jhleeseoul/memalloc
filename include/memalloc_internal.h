#ifndef MEMALLOC_INTERNAL_H
#define MEMALLOC_INTERNAL_H

#include <stddef.h>

typedef struct block {
    size_t size;
    int free;
    struct block* next;
} block_t;

block_t* get_free_list_head();
block_t* find_fit(size_t size);

void split_block(block_t* block, size_t size);
void coalesce_blocks();

#endif
