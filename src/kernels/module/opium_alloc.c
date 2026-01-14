#include "core/opium_core.h"
#include "kernels/opium_os.h"
#include "opium_alloc.h"

static void opium_allocator(opium_allocator_t *allocator)
{
   opium_allocator_ctl_t *ctl = opium_allocator_ctl(allocator);
#ifdef OPIUM_POSIX 
   ctl->mmap     = pos1x_mmap;
   ctl->munmap   = pos1x_munmap;
   ctl->memalign = pos1x_memalign;
#endif
}

   opium_s32_t 
opium_allocator_init(opium_allocator_t *allocator, opium_log_t *log)
{
   opium_allocator(allocator);
   opium_allocator_ctl_t *ctl = opium_allocator_ctl(allocator);
   void *ptr = ctl->mmap(NULL, 123, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_EXECUTABLE, -1, 0, log);
   return OPIUM_RET_OK;
}

   opium_allocator_ctl_t * 
opium_allocator_ctl(opium_allocator_t *allocator)
{
   return &allocator->ctl;
}
