#ifndef OPIUM_PROCESS_CPU_INCLUDED_H 
#define OPIUM_PROCESS_CPU_INCLUDED_H

#include "core/opium_core.h"

typedef struct {
   opium_s32_t    nice;
   opium_s32_t    policy;
   opium_cpuset_t affinity;
} opium_process_cpu_config_t;

typedef struct {
   opium_u64_t utime;
   opium_u64_t stime;
   opium_u64_t cpu_ticks;
} opium_process_cpu_metric_t;

extern opium_process_base_handler_t cpu_handler;

void opium_process_cpu_set_affinity(opium_u64_t *mask, size_t n);
void opium_process_cpu_set_policy(opium_s32_t policy);
void opium_process_cpu_set_nice(opium_s32_t nice);

#endif /* OPIUM_PROCESS_CPU_INCLUDED_H */
