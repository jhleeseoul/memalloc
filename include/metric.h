#ifndef METRIC_H
#define METRIC_H

#include <stddef.h>

double measure_avg_alloc_time(size_t size, int iterations);
double calculate_external_fragmentation();
double calculate_heap_utilization();

#endif
