#ifndef OPIUM_ARRAY_INCLUDE_H 
#define OPIUM_ARRAY_INCLUDE_H 

#include "core/opium_core.h"

typedef struct {
   size_t     index;
   opium_u8_t alive;
} opium_array_head_t;

struct opium_array_s {
   void        *data;
   size_t       size;

   size_t       elt_size;
   size_t       elts_max;
   size_t       elts_n;

   opium_log_t *log;
};

opium_s32_t opium_array_is_initialized(opium_array_t *arr);

opium_s32_t opium_array_create(opium_array_t *arr, size_t elts_max, size_t elt_size, opium_log_t *log);
void        opium_array_destroy(opium_array_t *arr);

void       *opium_array_push(opium_array_t *arr, void *element);
void        opium_array_pop(opium_array_t *arr, size_t index); 
void       *opium_array_get(opium_array_t *arr, size_t index);

void       *opium_array_get(opium_array_t *arr, size_t index);
size_t      opium_array_index(opium_array_t *arr, void *data);

size_t      opium_array_size(opium_array_t *arr);
size_t      opium_array_capacity(opium_array_t *arr);
opium_s32_t opium_array_full(opium_array_t *arr);

#endif /* OPIUM_ARRAY_INCLUDE_H */
