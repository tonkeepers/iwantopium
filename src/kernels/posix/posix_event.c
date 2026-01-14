#include "core/opium_core.h"
#include "posix.h"

   opium_s32_t
pos1x_event_init(void *beggar, opium_size_t elts_max, opium_log_t *log)
{
   opium_size_t size;

   size = sizeof(pos1x_event_t);
   pos1x_event_t *data = opium_calloc(size, log);
   if (!data) {
      opium_log_err(log, "Posix: Failed to allocate event data! Size: %zu\n", size);
      return OPIUM_RET_ERR;
   }

   data->fd = epoll_create(EPOLL_CLOEXEC);
   if (data->fd < 0) {
      opium_log_err(log, "Posix: Failed to epoll_create event!\n"); 
      pos1x_event_exit(data, log);
   }

   size = elts_max * sizeof(struct epoll_event);
   data->events = opium_calloc(size, log); 
   if (!data->events) {
      opium_log_err(log, "Posix: Failed to allocate event! Size: %zu\n", size);
      pos1x_event_exit(data, log);
   }

   beggar = data;

   return OPIUM_RET_OK;
}

   void 
pos1x_event_exit(void *beggar, opium_log_t *log)
{
   pos1x_event_t *data = (pos1x_event_t *)beggar;

   if (data->fd > 0) {
      close(data->fd);
      data->fd = -1;
   }

   if (data->events) {
      opium_free(data->events, log);
      data->events = NULL;
   }
}
