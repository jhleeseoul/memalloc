#include <stdio.h>
#include <string.h>
#include "include/memalloc.h"
#include "include/metric.h"

void run_workload(alloc_policy_t policy);

int main() {
    printf("=== 사용자 정의 메모리 할당기 테스트 ===\n");

    init_heap();                     // 힙 초기화
    set_alloc_policy(FIRST_FIT);     // 정책 설정 (변경 가능)

    // 1. 할당
    char* a = (char*)my_malloc(100);
    char* b = (char*)my_malloc(200);
    char* c = (char*)my_malloc(50);

    if (a && b && c) {
        printf("[할당 완료] a, b, c 블록\n");

        // 2. 값 쓰기
        strcpy(a, "Block A data");
        strcpy(b, "Block B data");
        strcpy(c, "Block C data");

        printf("a = %s\n", a);
        printf("b = %s\n", b);
        printf("c = %s\n", c);
    } else {
        printf("[에러] 메모리 할당 실패\n");
    }

    // 3. 해제
    my_free(b);
    printf("[해제] b 블록\n");

    // 4. 다시 할당 (b 자리 재사용 여부 확인)
    char* d = (char*)my_malloc(180);  // b보다 약간 작은 크기
    if (d) {
        strcpy(d, "Block D reuses B");
        printf("d = %s\n", d);
    } else {
        printf("[에러] d 블록 할당 실패\n");
    }

    // 5. 외부 단편화 비율 측정
    double avg_time = measure_avg_alloc_time(64, 1000);
    printf("평균 할당 시간 (64B x 1000): %.8f초\n", avg_time);

    double frag = calculate_external_fragmentation();
    printf("외부 단편화 비율: %.2f%%\n", frag * 100);

    double util = calculate_heap_utilization();
    printf("힙 사용률: %.2f%%\n", util * 100);


    run_workload(FIRST_FIT);
    run_workload(BEST_FIT);
    run_workload(NEXT_FIT);

    return 0;
}
