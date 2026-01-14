#ifndef OPIUM_ALLOC_INCLUDED_H
#define OPIUM_ALLOC_INCLUDED_H

#include "core/opium_core.h"

typedef struct opium_allocator_s opium_allocator_t;

typedef struct {
   void *(*mmap)(void *addr, opium_size_t len, opium_s32_t prot, opium_s32_t flags, 
         opium_fd_t fd, opium_off_t offset, opium_log_t *log);

   void  (*munmap)(void *data, opium_size_t size, opium_log_t *log);
   void *(*memalign)(opium_size_t align, opium_size_t size, opium_log_t *log);
} opium_allocator_ctl_t;

struct opium_allocator_s {
   opium_allocator_ctl_t ctl;

   opium_size_t          size;
   opium_size_t          calls;

   opium_log_t          *log;
};



#endif /* OPIUM_ALLOC_INCLUDED_H */
