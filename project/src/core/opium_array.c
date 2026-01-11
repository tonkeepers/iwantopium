#include "core/opium_core.h"

#define OPIUM_ARRAY_HEADER_SIZE sizeof(opium_array_head_t)

static size_t opium_array_offset(opium_array_t *arr, size_t index)
{
   if (index >= arr->elts_max) {
      opium_log_err(arr->log, "Index out of bounds. Index: %zu, Max Elts: %zu\n", index, arr->elts_max);
      return (size_t)-1;
   }

   return index * arr->elt_size;
}

static opium_array_head_t *opium_array_slot(opium_array_t *arr, size_t index)
{
   size_t offset = opium_array_offset(arr, index);
   if (offset == (size_t)-1) {
      return NULL;
   }

   return (opium_array_head_t*)((char *)arr->data + offset);
}

static void *opium_array_data_from_head(void *slot)
{
   return (char *)slot + OPIUM_ARRAY_HEADER_SIZE;
}

static void *opium_array_head_from_data(void *slot)
{
   return (char *)slot - OPIUM_ARRAY_HEADER_SIZE;
}

   opium_s32_t 
opium_array_is_initialized(opium_array_t *arr)
{
   return !arr->data ? OPIUM_RET_ERR : OPIUM_RET_OK;
}

   opium_s32_t 
opium_array_create(opium_array_t *arr, size_t elts_max, size_t elt_size, opium_log_t *log)
{
   void *result;
   size_t relt_size = elt_size + OPIUM_ARRAY_HEADER_SIZE;
   size_t size = elts_max * relt_size;

   result = opium_calloc(size, log);
   if (opium_unlikely(!result)) {
      opium_log_err(log, "Failed to allocate array. Size: %zu.\n", size);
      return OPIUM_RET_ERR;
   }

   arr->data     = result;

   arr->size     = size;

   arr->elt_size = relt_size;
   arr->elts_max = elts_max;
   arr->elts_n   = 0;

   arr->log      = log;

   return OPIUM_RET_OK;
}

   void           
opium_array_destroy(opium_array_t *arr)
{
   if (opium_likely(arr->data)) {
      opium_free(arr->data, arr->log);
      arr->data = NULL;
   }

   arr->size     = 0;

   arr->elt_size = 0;
   arr->elts_max = 0;
   arr->elts_n   = 0;

   arr->log      = NULL;
}

   void * 
opium_array_push(opium_array_t *arr, void *element)
{
   if (arr->elts_n >= arr->elts_max) {
      opium_log_err(arr->log, "Array is full (capacity = %zu)\n", arr->elts_max);
      return NULL;
   }

   opium_array_head_t *head = opium_array_slot(arr, arr->elts_n);
   if (!head) {
      return NULL;
   }

   head->alive = 1;
   head->index = arr->elts_n;

   void *data = opium_array_data_from_head(head);
   size_t user_data_size = arr->elt_size - OPIUM_ARRAY_HEADER_SIZE;

   opium_memcpy(data, element, user_data_size);

   arr->elts_n = arr->elts_n + 1;

   return data;
}

   void 
opium_array_pop(opium_array_t *arr, size_t index) 
{
   if (arr->elts_n <= 0) {
      opium_log_err(arr->log, "Array is empty, cannot pop.\n");
      return;
   }

   opium_array_head_t *head = opium_array_slot(arr, index);
   if (!head) {
      return;
   }

   if (head->alive != 1) {
      opium_log_err(arr->log, "Slot already dead (index = %zu)\n", index);
      return;
   }

   head->alive = 0;
   arr->elts_n = arr->elts_n - 1;
}

   void *
opium_array_get(opium_array_t *arr, size_t index)
{
   opium_array_head_t *head = opium_array_slot(arr, index);
   if (!head) {
      return NULL;
   }

   if (head->alive != 1) {
      opium_log_err(arr->log, "Slot is not alive (index = %zu)\n", index);
      return NULL;
   }

   return opium_array_data_from_head(head);
}

   size_t
opium_array_index(opium_array_t *arr, void *data)
{
   char *ptr = (char *)data;
   char *base = (char *)arr->data;

   if (ptr < base || ptr >= base + arr->size) {
      opium_log_err(arr->log, "Pointer is outside array range\n");
      return (size_t)-1;
   }

   ptrdiff_t offset = ptr - (base - OPIUM_ARRAY_HEADER_SIZE);
   if (offset < 0) {
      opium_log_err(arr->log, "Pointer points inside header\n");
      return (size_t)-1;
   }

   if (offset % arr->elt_size != 0) {
      opium_log_err(arr->log, "Pointer is not aligned to element boundary\n");
      return (size_t)-1;
   }

   size_t index = offset / arr->elt_size;

   if (index >= arr->elts_max) {
      return (size_t)-1;
   }

   return index;
}

   size_t
opium_array_size(opium_array_t *arr)
{
   return arr->size;
}

   size_t 
opium_array_capacity(opium_array_t *arr)
{
   return arr->elts_max;
}

   opium_s32_t
opium_array_full(opium_array_t *arr)
{
   return arr->elts_n == arr->elts_max ? OPIUM_RET_OK : OPIUM_RET_ERR;
}
