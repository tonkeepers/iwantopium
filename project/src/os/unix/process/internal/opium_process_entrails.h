#ifndef OPIUM_PROCESS_ENTRAILS_INCLUDED_H
#define OPIUM_PROCESS_ENTRAILS_INCLUDED_H

#include "core/opium_core.h"

typedef struct {
   opium_slab_t        *slab;

   opium_process_base_t cpu;
   opium_process_base_t memory;

   opium_log_t         *log;
} opium_process_entrails_t;

opium_s32_t opium_entrails_init(opium_process_entrails_t *entrails, opium_log_t *log);

#endif /* OPIUM_PROCESS_ENTRAILS_INCLUDED_H */
