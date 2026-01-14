#include "core/opium_core.h"

   void *
opium_malloc(size_t size, opium_log_t *log)
{
   void *ptr = malloc(size);
   if (!ptr) {
      opium_log_debug(log, "Malloc failed(size: %zu)\n", size);
   }

   opium_log_debug(log, "Allocate pointer. Size: %zu\n", size);

   return ptr;
}

   void *
opium_calloc(size_t size, opium_log_t *log)
{
   void *ptr = opium_malloc(size, log);

   if (ptr) {
      opium_memzero(ptr, size);
   }

   return ptr;
}

   void
opium_free(void *ptr, opium_log_t *log)
{
   if (!ptr) return;
   free(ptr);
   (void)log;
}

