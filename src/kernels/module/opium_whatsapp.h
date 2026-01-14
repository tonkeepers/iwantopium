#ifndef OPIUM_WHATSAPP_INCLUDED_1H
#define OPIUM_WHATSAPP_INCLUDED_1H

#include "core/opium_core.h"

#define OPIUM_WA_READ     0x002
#define OPIUM_WA_WRITE    0x004
#define OPIUM_WA_ERROR    0x008
#define OPIUM_WA_HANGUP   0x010
#define OPIUM_WA_PRIORITY 0x020
#define OPIUM_WA_EDGE     0x040

typedef struct opium_whatsapp_s opium_whatsapp_t;

typedef struct {
   opium_whatsapp_t *(*init)(void *data, opium_size_t elts_max, opium_log_t *log);
   void              (*destroy)(opium_whatsapp_t *wa);

   opium_s32_t       (*add)(opium_whatsapp_t *wa, opium_fd_t fd,
         opium_u32_t ev, void *data);
   opium_s32_t       (*modify)(opium_whatsapp_t *wa, opium_fd_t fd,
         opium_u32_t ev, void *data);
   opium_s32_t       (*remove)(opium_whatsapp_t *wa, opium_fd_t fd);

   opium_s32_t       (*track)(opium_whatsapp_t *wa,
         opium_s32_t timeout_ms);
} opium_whatsapp_ctl_t;

struct opium_whatsapp_s {
   void                   *implementation;

   opium_whatsapp_ctl_t    ctl;

   opium_size_t            elts_n;
   opium_size_t            elts_max;

   opium_log_t            *log;
};

opium_s32_t opium_whatsapp_init(opium_whatsapp_t *wa, opium_size_t elts_max, opium_log_t *log);

#endif /* OPIUM_WHATSAPP_INCLUDED_H */
