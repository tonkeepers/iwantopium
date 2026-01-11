#include "core/opium_core.h"

   opium_process_base_t * 
opium_process_base_create(opium_slab_t *slab, char *name, size_t cs, size_t ms, opium_log_t *log)
{
   void *resultp[2];

   resultp[0] = opium_calloc(cs, log);
   if (!resultp[0]) {
      opium_log_err(log, "Failed to allocate config. Size: %zu\n", cs);
      goto err;
   }

   resultp[1] = opium_calloc(ms, log);
   if (opium_unlikely(!resultp[1])) {
      opium_log_err(log, "Failed to allocate metric. Size: %zu\n", ms);
      goto free_ptr0;
   }

   opium_process_base_t *base = opium_slab_alloc(slab); 
   if (opium_unlikely(!base)) {
      opium_log_err(log, "Failed to allocate base. Size: %zu\n", sizeof(opium_process_base_t));
      goto free_ptr1;
   }

   base->slab        = slab;

   base->name        = name;

   base->enabled     = false;
   base->initialized = false;

   base->config      = resultp[0];
   base->config_size = cs;

   base->metric      = resultp[1];
   base->metric_size = ms;

   base->log         = log;

   return base;

free_ptr1:
   opium_free(resultp[1], log);
free_ptr0:
   opium_free(resultp[0], log);
err:
   return NULL;
}

   void 
opium_process_base_exit(opium_process_base_t *base)
{
   if (opium_likely(base->config)) {
      opium_free(base->config, base->log);
   }

   if (opium_likely(base->metric)) {
      opium_free(base->metric, base->log);
   }

   opium_slab_free(base->slab, base);
}

   void 
opium_process_base_bind(opium_process_base_t *base, opium_process_base_func_t *func)
{
   base->func = *func;
}


   opium_s32_t
opium_process_base_enable(opium_process_base_t *base)
{
   if (opium_likely(!base->initialized && !base->enabled)) {
      base->func.init(base);
      base->initialized = true;
   }

   base->enabled = true;

   return OPIUM_RET_OK;
}

   opium_s32_t
opium_process_base_config_apply(opium_process_base_t *base)
{
   opium_s32_t resultn;

   if (base->func.config_validate) {
      resultn = base->func.config_validate(base->config);
      if (resultn != OPIUM_RET_OK) {
         return OPIUM_RET_ERR;
      }
   }

   return base->func.config_apply(base->config);
}

   opium_s32_t
opium_process_base_metric_collect(opium_process_base_t *base)
{
   if (!base->func.metric_collect) {
      return OPIUM_RET_ERR;
   }

   return base->func.metric_collect(base->metric);
}

   void *
opium_process_base_get_config(opium_process_base_t *base)
{
   return base->config;
}

   void *
opium_process_base_get_metric(opium_process_base_t *base)
{
   return base->metric;
}
