#include "core/opium_core.h"

/*
 * Process Architecture Overview
 *
 * 1. entrails/  — internal organs of the process
 *    A process, like a living organism, has core “organs”: CPU, memory,
 *    file descriptors.  Entrails operate strictly from within, never
 *    reaching outside the process boundary.
 *
 * 2. api/  — structural foundation (skeleton)
 *    opium_process_base.h/c define the abstractions on which everything
 *    else relies — similar to OOP interfaces or virtual tables.
 *    They specify *how* subsystems must interact, without dictating *what*
 *    they do.  A common contract ensures uniform behavior across CPU,
 *    memory, and other modules.
 *
 * 3. subsystems/  — specialized organs
 *    opium_process_cpu.h/c     — cognitive center: CPU affinity, priority
 *    opium_process_memory.h/c  — memory manager: limits, allocation tracking
 *
 *    Each subsystem focuses on a single internal function and registers
 *    itself with the base API, declaring its capabilities (e.g., “I handle
 *    CPU”, “I enforce memory limits”).
 *
 * 4. config/  — prescribed anatomy and policies (the recipe)
 *    opium_process_config.h/c stores the *desired state*:
 *      “Run on CPU cores 0–2”, “Limit memory to 1 GiB”.
 *    Config provides intent, not execution — subsystems turn instruction
 *    into action.  Think of config as a recipe and subsystems as chefs.
 *
 * 5. metric/  — diagnostics and health reports
 *    opium_process_metric.h/c collect real-time information:
 *      “CPU load = 30%”, “Current memory usage = 512 MiB”.
 *    Metrics observe, never modify — vital for monitoring, logging, and
 *    feedback loops.
 *
 * 6. opium_process_entrails.h/c  — chief coordinator (chief physician)
 *    The conductor that integrates config, metrics, and all subsystems.
 *    Responsibilities:
 *      • Apply configuration across organs
 *      • Collect and aggregate metrics
 *      • Handle “change settings” requests
 *      • Monitor ongoing health of the process
 *
 * Together, these components form a modular internal control system where
 * each subsystem remains simple, focused, and replaceable — yet all speak
 * a shared architectural language.
 *
 */
/*
   opium_s32_t
opium_entrails_init(opium_process_entrails_t *entrails, opium_log_t *log)
{
   opium_s32_t resultn;

   size_t cs;
   size_t ms;

   cs = sizeof(opium_process_cpu_config_t);
   ms = sizeof(opium_process_cpu_metric_t);

   resultn = opium_process_base_create(&entrails->cpu, cs, ms, log);
   if (resultn != OPIUM_RET_OK) {
      opium_log_err(log, "Failed to allocate cpu base! Config size: %zu, Metric size: %zu\n", cs, ms);
      return OPIUM_RET_ERR;
   }

   opium_process_base_bind(&entrails->cpu, &cpu_handler); 
  
   opium_process_base_handler_t *handler = opium_process_base_handler(&entrails->cpu);

   opium_u64_t mask[] = {0, 3};
   size_t size = sizeof(mask) - sizeof(mask[0]);
   opium_process_cpu_set_affinity(mask, size);
   
   entrails->log = log;

   return OPIUM_RET_OK;
}*/
