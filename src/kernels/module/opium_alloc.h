#ifndef OPIUM_ALLOC_INCLUDED_H
#define OPIUM_ALLOC_INCLUDED_H

#include "core/opium_core.h"

typedef struct opium_allocator_s opium_allocator_t;

typedef struct {
   opium_size_t peak_usage;
   opium_size_t current_usage;
   opium_size_t allocation_count;
   opium_size_t error_count;
} opium_alloc_stats_t;

typedef struct {
   void *(*mmap)(void *addr, opium_size_t len, opium_s32_t prot, opium_s32_t flags, 
         opium_fd_t fd, opium_off_t offset, opium_log_t *log);

   void  (*munmap)(void *data, opium_size_t size, opium_log_t *log);
   void *(*memalign)(opium_size_t align, opium_size_t size, opium_log_t *log);
} opium_allocator_ctl_t;

struct opium_allocator_s {
   opium_allocator_ctl_t ctl;

   opium_alloc_stats_t   stats;
   opium_s32_t           tracing;

   opium_log_t          *log;
};

opium_s32_t opium_allocator_init(opium_allocator_t *allocator, opium_log_t *log);

opium_allocator_ctl_t *opium_allocator_ctl(opium_allocator_t *allocator);

#endif /* OPIUM_ALLOC_INCLUDED_H */
