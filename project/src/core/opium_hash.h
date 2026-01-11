#ifndef OPIUM_HASH_INCLUDE_H
#define OPIUM_HASH_INCLUDE_H

#include "core/opium_core.h"

typedef opium_u64_t (*opium_hash_func_t)(void *raw_key, size_t key_size);

typedef struct {
   void             *key;
   void             *value;
   size_t            len;
   opium_rbt_t       rbt;
} opium_hash_entry_t;

struct opium_hash_s {


   size_t            elts_max;
   size_t            elts_n;

   opium_hash_func_t func;

   opium_log_t      *log;
};

#endif /* OPIUM_HASH_INCLUDE_H */
