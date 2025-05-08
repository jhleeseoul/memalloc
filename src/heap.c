#include "memalloc.h"
#include "memalloc_internal.h"
#include <stdint.h>

#define ALIGN4(size) (((size) + 3) & ~0x3)

static char heap[HEAP_SIZE];       // 실제 힙 메모리
static block_t* free_list = NULL;  // 첫 블록 (free block 리스트 시작점)

void init_heap() {
    free_list = (block_t*)heap;
    free_list->size = HEAP_SIZE - sizeof(block_t);
    free_list->free = 1;
    free_list->next = NULL;
}

block_t* get_free_list_head() {
    return free_list;
}

void split_block(block_t* block, size_t size) {
    if (block->size >= size + sizeof(block_t) + 4) {
        block_t* new_block = (block_t*)((char*)block + sizeof(block_t) + size);
        new_block->size = block->size - size - sizeof(block_t);
        new_block->free = 1;
        new_block->next = block->next;

        block->size = size;
        block->next = new_block;
    }
}

void coalesce_blocks() {
    block_t* curr = free_list;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += sizeof(block_t) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}
