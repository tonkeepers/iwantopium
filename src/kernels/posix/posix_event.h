#ifndef OPIUM_POSIX_EVENT_INCLUDED_H
#define OPIUM_POSIX_EVENT_INCLUDED_H

#include "core/opium_core.h"

typedef struct pos1x_event_s pos1x_event_t;

struct pos1x_event_s {
   opium_fd_t          fd;
   struct epoll_event *events;
};

opium_s32_t pos1x_event_init(void *beggar, opium_size_t elts_max, opium_log_t *log);
void        pos1x_event_exit(void *beggar, opium_log_t *log);

#endif /* OPIUM_POSIX_EVENT_INCLUDED_H */
