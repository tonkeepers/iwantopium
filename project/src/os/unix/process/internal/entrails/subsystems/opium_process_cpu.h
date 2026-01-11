#ifndef OPIUM_PROCESS_CPU_INCLUDED_H 
#define OPIUM_PROCESS_CPU_INCLUDED_H

#include "core/opium_core.h"

typedef struct {
   opium_s32_t    nice;
   opium_s32_t    policy;
   opium_cpuset_t affinity;
} opium_process_cpu_config_t;

typedef struct {
   opium_u64_t user_ticks;
   opium_u64_t system_ticks;
   opium_u64_t total_ticks;
   opium_u64_t usage_percent;
   opium_u64_t last_update;
} opium_process_cpu_metric_t;

extern opium_process_base_func_t cpu_handler;

void opium_process_cpu_set_affinity(opium_u64_t *mask, size_t n);
void opium_process_cpu_set_policy(opium_s32_t policy);
void opium_process_cpu_set_nice(opium_s32_t nice);

#endif /* OPIUM_PROCESS_CPU_INCLUDED_H */
