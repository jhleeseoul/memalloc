#include "memalloc.h"
#include "memalloc_internal.h"
#include <stddef.h>
#include <string.h> // memset
#include <stdint.h> // uintptr_t for pointer alignment

#define ALIGN4(size) (((size) + 3) & ~0x3)

void* my_malloc(size_t size) {
    size = ALIGN4(size);  // 4바이트 정렬

    block_t* block = find_fit(size);
    if (!block) {
        return NULL;  // 메모리 부족
    }

    split_block(block, size);
    block->free = 0;

    // 유저에게는 데이터 영역만 노출
    return (void*)((char*)block + sizeof(block_t));
}

void my_free(void* ptr) {
    if (!ptr) return;

    block_t* block = (block_t*)((char*)ptr - sizeof(block_t));
    block->free = 1;

    coalesce_blocks();  // 병합 시도 (단순 구현: 전체 순회)
}
