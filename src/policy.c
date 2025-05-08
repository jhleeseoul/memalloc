#include "memalloc.h"
#include "memalloc_internal.h"

// heap.c에 정의된 내부 구조와 전역 변수 접근
extern block_t* get_free_list_head();
static block_t* last_alloc = NULL;  // next-fit에서 사용

static alloc_policy_t current_policy = FIRST_FIT;

void set_alloc_policy(alloc_policy_t policy) {
    current_policy = policy;
}

block_t* find_first_fit(size_t size) {
    block_t* curr = get_free_list_head();
    while (curr) {
        if (curr->free && curr->size >= size) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

block_t* find_best_fit(size_t size) {
    block_t* best = NULL;
    block_t* curr = get_free_list_head();
    while (curr) {
        if (curr->free && curr->size >= size) {
            if (!best || curr->size < best->size) {
                best = curr;
            }
        }
        curr = curr->next;
    }
    return best;
}

block_t* find_next_fit(size_t size) {
    block_t* curr = last_alloc ? last_alloc->next : get_free_list_head();
    if (!curr) curr = get_free_list_head();

    block_t* start = curr;
    do {
        if (curr->free && curr->size >= size) {
            last_alloc = curr;
            return curr;
        }
        curr = curr->next ? curr->next : get_free_list_head();
    } while (curr != start);
    return NULL;
}

// 공통 인터페이스: 현재 정책에 맞는 블록 탐색
block_t* find_fit(size_t size) {
    switch (current_policy) {
        case FIRST_FIT: return find_first_fit(size);
        case BEST_FIT: return find_best_fit(size);
        case NEXT_FIT: return find_next_fit(size);
        default: return NULL;
    }
}
