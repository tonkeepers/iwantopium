/* @file opium_alloc.c
 * @brief Memory allocation wrappers for the Opium core library
 *
 * This module provides thin wrappers around standard C allocation
 * functions (malloc, calloc, free, posix_memalign), with integrated
 * logging support. It ensures that every memory operation can be 
 * tracked and debugged consistently.
 *
 */

#include "core/opium_core.h"
#include "posix.h"

   void *
pos1x_mmap(void *addr, opium_size_t len, opium_s32_t prot, opium_s32_t flags, opium_fd_t fd, 
      opium_off_t offset, opium_log_t *log)
{
   void *ptr = NULL;

   ptr = mmap(addr, len, prot, flags, fd, offset);
   if (!ptr) {
      opium_log_debug(log, "mmap failed(size: %zu)\n", len);
      ptr = NULL;  
   }

   return ptr;
}

void
pos1x_munmap(void *data, opium_size_t size, opium_log_t *log) {
   if (munmap(data, size) == -1) {
      opium_log_debug(log, "munmap failed(size: %zu)\n", size);
   }
}

void *
pos1x_memalign(opium_size_t align, opium_size_t size, opium_log_t *log) {
   void *ptr = NULL;
   int err;

   err = posix_memalign(&ptr, align, size);
   if (err < 0) {
      opium_log_debug(log, "posix_memalign failed(size: %zu)\n", size);
      ptr = NULL;  
   }

   opium_log_debug(log, "posix_memalign(ptr: %p, al: %zu, size: %zu)\n",
         ptr, align, size);

   return ptr;
}
