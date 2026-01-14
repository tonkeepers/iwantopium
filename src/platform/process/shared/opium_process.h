#ifndef OPIUM_PROCESS_INCLUDED_H
#define OPIUM_PROCESS_INCLUDED_H

#include "core/opium_core.h"

typedef opium_uintptr_t opium_process_id;

struct opium_process_s {
   opium_process_id id;

   void             (*create)();
   
};

#endif /* OPIUM_PROCESS_INCLUDED_H */
