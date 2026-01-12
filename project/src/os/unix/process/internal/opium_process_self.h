#ifndef OPIUM_PROCESS_INCLUDED_H 
#define OPIUM_PROCESS_INCLUDED_H 

#include "core/opium_core.h"

struct opium_process_s {
   opium_pid_t              pid;
   opium_pid_t              ppid;

   char                    *name;
   void                    *data;

   opium_process_entrails_t entrails;

   opium_log_t             *log;
};

void opium_process_init(opium_process_t self, char *name, void *data, opium_log_t *log);

#endif /* OPIUM_PROCESS_INCLUDED_H  */
