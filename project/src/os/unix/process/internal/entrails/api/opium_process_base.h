#ifndef OPIUM_PROCESS_BASE_INCLUDED_H
#define OPIUM_PROCESS_BASE_INCLUDED_H

#include "core/opium_core.h"

typedef struct {
   opium_s32_t (*init)(void *context);

   opium_s32_t (*config_validate)();
   opium_s32_t (*config_apply)();
   opium_s32_t (*config_reset)();

   opium_s32_t (*metric_collect)();
   opium_s32_t (*metric_diff)(void *metric_old);

} opium_process_base_handler_t;

typedef struct {
   opium_slab_t                *slab;

   void                        *config;
   size_t                       config_size;

   void                        *metric;
   size_t                       metric_size;

   unsigned                     initialized:1;
   unsigned                     enabled:1;
   unsigned                     reserved:6;

   opium_process_base_handler_t handler;

   opium_log_t                 *log;
} opium_process_base_t;

opium_s32_t opium_process_base_create(opium_process_base_t *base, size_t cs, size_t ms, opium_log_t *log);
void        opium_process_base_exit(opium_process_base_t *base);

void        opium_process_base_bind(opium_process_base_t *base, opium_process_base_handler_t *handler);

opium_s32_t opium_process_base_enable(opium_process_base_t *base);
opium_s32_t opium_process_base_config_apply(opium_process_base_t *base);
opium_s32_t opium_process_base_metric_collect(opium_process_base_t *base);

void       *opium_process_base_get_config(opium_process_base_t *base);
void       *opium_process_base_get_metric(opium_process_base_t *base);


opium_process_base_handler_t *opium_process_base_handler(opium_process_base_t *base); 

#endif /* OPIUM_PROCESS_BASE_INCLUDED_H */
