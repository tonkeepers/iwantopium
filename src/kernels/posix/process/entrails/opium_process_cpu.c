/*#include "core/opium_core.h"

static opium_process_base_t *base;

static opium_s32_t init(void *context); 
static opium_s32_t config_validate(void); 
static opium_s32_t config_apply(void); 
static opium_s32_t config_reset(void);
static opium_s32_t metric_collect(void);

static opium_s32_t set_affinity(pid_t pid, opium_cpuset_t *mask);
static opium_s32_t set_policy(pid_t pid, opium_s32_t policy);
static opium_s32_t set_nice(pid_t pid, opium_s32_t nice);

static opium_process_cpu_config_t *getconfig(opium_process_base_t *base);
static opium_process_cpu_metric_t *getmetric(opium_process_base_t *base);

const opium_cpuset_t cpu_affinity_default[] = {0};
const opium_s32_t    cpu_policy_default     = SCHED_OTHER;
const opium_s32_t    cpu_nice_default       = 0;

opium_process_base_handler_t cpu_handler = {
   .init            = init,
   .config_validate = config_validate,
   .config_apply    = config_apply,
   .config_reset    = config_reset,
   .metric_collect  = metric_collect
};

#pragma region PUBLIC_API

void opium_process_cpu_set_affinity(opium_u64_t *mask, size_t n)
{
   opium_process_cpu_config_t *config = getconfig(base);
   CPU_ZERO(&config->affinity);

   for (size_t index = 0; index < n; index++) {
      CPU_SET(mask[index], &config->affinity);
   }
}

void opium_process_cpu_set_policy(opium_s32_t policy)
{
   opium_process_cpu_config_t *config = getconfig(base);
   config->policy = policy;
}

void opium_process_cpu_set_nice(opium_s32_t nice)
{
   opium_process_cpu_config_t *config = getconfig(base);
   config->nice = nice;
}

#pragma endregion

#pragma region HANDLER_IMPLEMENTATIONS

static opium_s32_t init(void *context)
{
   base = (opium_process_base_t *)context;

   return OPIUM_RET_OK;
}

static opium_s32_t config_validate() 
{
   opium_process_cpu_config_t *conf = getconfig(base); 

   opium_s32_t resultn;

   opium_cpuset_t *affinity = &conf->affinity;
   opium_s32_t     policy = conf->policy;
   opium_s32_t     nice = conf->nice;

   opium_s32_t     nice_max = sched_get_priority_max(SCHED_OTHER);
   opium_s32_t     nice_min = sched_get_priority_min(SCHED_OTHER);

   if (nice < nice_min || nice > nice_max) {
      opium_log_err(base->log, "Invalid nice value: %d (must be %d to %d)", conf->nice, nice_min, nice_max);
      return OPIUM_RET_ERR;
   }

   switch (policy) {
      case SCHED_OTHER:
      case SCHED_FIFO:
      case SCHED_RR:
      case SCHED_BATCH:
      case SCHED_IDLE:
      case SCHED_DEADLINE:
         break;

      default:
         opium_log_err(base->log, "Invalid scheduling policy: %d", conf->policy); 
         return OPIUM_RET_ERR;
   }

   opium_s32_t cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
   if (cpu_count <= 0) {
      opium_log_err(base->log, "Failed to get CPU count");
      return OPIUM_RET_ERR;
   }

   if (cpu_count > 0) {
      opium_s32_t valid = 0;

      for (opium_s32_t index = 0; index < cpu_count && index < CPU_SETSIZE; index++) {
         if (CPU_ISSET(index, affinity)) {
            valid = valid + 1;
         }
      }

      if (valid == 0) {
         opium_log_err(base->log, "CPU affinity empty - no CPUs selected");
         return OPIUM_RET_ERR;
      }
   } 

   return OPIUM_RET_OK;
}

static opium_s32_t config_apply()
{
   opium_process_cpu_config_t *conf = getconfig(base); 

   opium_s32_t resultn;
   opium_pid_t pid = getpid();

   resultn = set_affinity(pid, &conf->affinity); 
   if (resultn != OPIUM_RET_OK) {

   }

   resultn = set_policy(pid, conf->policy);
   if (resultn != OPIUM_RET_OK) {

   }

   resultn = set_nice(pid, conf->nice);
   if (resultn != OPIUM_RET_OK) {

   }

   return OPIUM_RET_OK;
}

static opium_s32_t config_reset()
{
   opium_process_cpu_config_t *conf = getconfig(base); 

   opium_cpuset_t affinity = *cpu_affinity_default;
   CPU_ZERO(&affinity);
   CPU_SET(0, &affinity);

   conf->affinity = affinity;
   conf->policy   = cpu_policy_default;
   conf->nice     = cpu_nice_default;

   return OPIUM_RET_OK;
}

static opium_s32_t metric_collect()
{
   opium_process_cpu_metric_t *metric = getmetric(base);

   char *path = "/proc/self/stat";
   FILE *stat = fopen(path, "r"); 
   if (!stat) {
      opium_log_err(base->log, "Failed to open file: %s\n", path);
      return OPIUM_RET_ERR;
   }

   opium_u64_t utime = 0;
   opium_u64_t stime = 0;

   for (size_t index = 0; index < 13; index++) {
      fscanf(stat, "%*s");
   }

   fscanf(stat, "%lu %lu", &utime, &stime);

   opium_log_debug(base->log, "utime: %lu, stime: %lu\n", utime, stime);

   fclose(stat);

   return OPIUM_RET_OK;
}

#pragma endregion

#pragma region SYSTEM_CALLS

static opium_s32_t set_affinity(pid_t pid, opium_cpuset_t *mask)
{
   opium_s32_t resultn;

   resultn = sched_setaffinity(pid, sizeof(*mask), mask);
   if (resultn < 0) {
      return OPIUM_RET_ERR;
   }

   return OPIUM_RET_OK;
}

static opium_s32_t set_policy(pid_t pid, opium_s32_t policy)
{
   opium_s32_t        resultn;
   struct sched_param param;

   opium_memzero(&param, sizeof(struct sched_param));
   param.sched_priority = 1;

   resultn = sched_setscheduler(pid, policy, &param);
   if (resultn < 0) {
      return OPIUM_RET_ERR;
   }

   return OPIUM_RET_OK;
}

static opium_s32_t set_nice(pid_t pid, opium_s32_t nice)
{
   opium_s32_t resultn;

   resultn = setpriority(PRIO_PROCESS, pid, nice);
   if (resultn < 0) {
      return OPIUM_RET_ERR;
   }

   return OPIUM_RET_OK;
}

#pragma endregion

#pragma region INTERNAL_HELPERS

static opium_process_cpu_config_t *getconfig(opium_process_base_t *base_ptr)
{
   return (opium_process_cpu_config_t *)(opium_process_base_get_config(base_ptr));
}

static opium_process_cpu_metric_t *getmetric(opium_process_base_t *base_ptr)
{
   return (opium_process_cpu_metric_t *)(opium_process_base_get_metric(base_ptr));
}

#pragma endregion*/
