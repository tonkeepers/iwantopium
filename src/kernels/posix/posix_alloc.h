#ifndef OPIUM_POSIX_ALLOC_INCLUDED_H
#define OPIUM_POSIX_ALLOC_INCLUDED_H

#include "core/opium_core.h"

void *pos1x_mmap(void *addr, opium_size_t len, opium_s32_t prot, opium_s32_t flags, opium_fd_t fd,
      opium_off_t offset, opium_log_t *log);

void  pos1x_munmap(void *data, opium_size_t size, opium_log_t *log);
void *pos1x_memalign(opium_size_t align, opium_size_t size, opium_log_t *log);

#endif /* OPIUM_POSIX_ALLOC_INCLUDED_H */
