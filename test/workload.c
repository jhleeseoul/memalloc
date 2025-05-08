#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memalloc.h"
#include "metric.h"

#define ITERATIONS 10000
#define BLOCK_SIZE 64 + (rand() % 128) // 64~192B 사이의 블록 크기

void run_workload(alloc_policy_t policy) {
    printf("\n=== 정책: %s ===\n", 
        policy == FIRST_FIT ? "First Fit" :
        policy == BEST_FIT  ? "Best Fit"  : "Next Fit");

    init_heap();             // 힙 초기화
    set_alloc_policy(policy);

    void* ptrs[5000];
    for (int i = 0; i < 5000; ++i) {
        size_t size = 32 + rand() % 128;
        ptrs[i] = my_malloc(size);
    }

    // 일부 해제 (단편화 유도)
    for (int i = 0; i < 5000; ++i) {
        if (i % 3 == 0) my_free(ptrs[i]);
    }

    double avg_time = measure_avg_alloc_time(BLOCK_SIZE, ITERATIONS);
    double frag = calculate_external_fragmentation();
    double util = calculate_heap_utilization();

    printf("평균 할당 시간: %.8f초\n", avg_time);
    printf("외부 단편화 비율: %.2f%%\n", frag * 100);
    printf("힙 사용률: %.2f%%\n", util * 100);
}
