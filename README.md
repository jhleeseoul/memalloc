# 🧠 Custom Memory Allocator in C

> malloc과 free 없이 작동하는 사용자 정의 동적 메모리 할당기 구현 프로젝트입니다.
> 다양한 할당 정책(first-fit, best-fit, next-fit)을 비교하고, 실제 워크로드에서의 성능을 측정하여 분석합니다.

---

## 🚀 주요 기능

### 📦 사용자 정의 메모리 할당 및 해제

* 표준 `malloc()`/`free()` 없이 `my_malloc()`과 `my_free()` 구현
* 내부에서 직접 관리하는 1MB 힙에서 동작

### 🧠 다양한 할당 정책 지원

* **First Fit**: 처음 맞는 블록 할당
* **Best Fit**: 가장 작은 적합 블록 선택
* **Next Fit**: 이전 위치 이후부터 탐색 시작

### 📊 성능 측정 기능

* 평균 할당 시간 (allocation latency)
* 외부 단편화 비율
* 힙 사용률

### 🧪 워크로드 테스트 자동화

* 무작위 크기의 블록을 할당 및 일부 해제하는 시나리오 제공
* 정책별 성능을 수치로 비교 분석

### 📝 분석 보고서 포함

* 정책별 성능 차이를 정리한 Markdown 기반 리포트 (`report/analysis.md`)

---

## 🛠️ 기술 스택

| 항목    | 내용                 |
| ----- | ------------------ |
| 언어    | C                  |
| 실행 환경 | GCC 기반 Linux / WSL |
| 측정 도구 | clock() 사용 시간 측정   |

---

## 📁 프로젝트 구조

```
memalloc/
├── include/                 # 헤더 파일
│   ├── memalloc.h           # 외부 인터페이스
│   ├── memalloc_internal.h  # 내부 공유용 구조체 및 함수
│   └── metric.h             # 성능 측정 API
├── src/                     # 소스 파일
│   ├── memalloc.c           # my_malloc / my_free 구현
│   ├── heap.c               # 힙 관리 및 블록 구조
│   ├── policy.c             # 할당 정책 로직
│   └── metric.c             # 측정 함수 구현
├── test/
│   └── workload.c           # 워크로드 테스트 함수
├── report/
│   └── analysis.md          # 분석 보고서
├── main.c                   # 진입점 및 테스트 실행
└── Makefile                 # 빌드 스크립트
```

---

## 📊 예시 결과 (발췌)

```
=== 정책: First Fit ===
평균 할당 시간: 0.00001522초
외부 단편화 비율: 35.41%
힙 사용률: 44.17%

=== 정책: Best Fit ===
평균 할당 시간: 0.00004289초
외부 단편화 비율: 21.38%
힙 사용률: 38.72%

=== 정책: Next Fit ===
평균 할당 시간: 0.00001165초
외부 단편화 비율: 39.85%
힙 사용률: 41.30%
```

---

## 🔧 실행 방법

1. 클론 및 빌드:

```bash
git clone https://github.com/yourname/memalloc.git
cd memalloc
make
```

2. 실행:

```bash
./memtest
```

---

## ✅ 향후 개선 아이디어

* [ ] 내부 단편화 측정 기능 추가
* [ ] 힙 확장 (sbrk 시뮬레이션)
* [ ] 블록 통계 시각화 (graphviz 등)
* [ ] 동시성 환경에서의 allocator 실험

---

## 🙌 만든 사람

이 프로젝트는 시스템 프로그래밍 이해와 메모리 구조 분석 역량 강화를 위해 개발되었습니다.
피드백 및 개선 제안 환영합니다! ✉️

```
📛 이재현  
📧 jhleegit@gmail.com  
🌐 https://github.com/jhleegit
```

---

## 📄 라이선스

본 프로젝트는 MIT 라이선스를 따릅니다.
