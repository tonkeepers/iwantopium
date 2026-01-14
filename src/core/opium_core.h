#ifndef OPIUM_CORE_INCLUDE_H
#define OPIUM_CORE_INCLUDE_H

#include "opium.h"
#include "opium_types.h"

#ifdef __linux
#define OPIUM_LINUX 1
#endif

/* Detect pointer size: 32-bit vs 64-bit */
#if defined(__x86_64__) || defined(__ppc64__)
#define OPIUM_PTR_SIZE 8
#else
#define OPIUM_PTR_SIZE 4
#endif

#define OPIUM_RET_OK    0
#define OPIUM_RET_ERR  -1
#define OPIUM_RET_FULL -2

#define OPIUM_MEMCPY_LIMIT 2048
#define OPIUM_MEMSET_LIMIT 2048

typedef int8_t       opium_s8_t;
typedef int16_t      opium_s16_t;  
typedef int32_t      opium_s32_t;
typedef int64_t      opium_s64_t;

typedef uint8_t      opium_u8_t;
typedef uint16_t     opium_u16_t;
typedef uint32_t     opium_u32_t;
typedef uint64_t     opium_u64_t;

typedef uintptr_t    opium_uintptr_t;

typedef opium_s8_t   opium_key_t;
typedef opium_s8_t   opium_flag_t;

#define opium_flag_true(flag)    ((flag) = 1)
#define opium_flag_false(flag)   ((flag) = 0)
#define opium_flag_istrue(flag)  ((flag) == 1)
#define opium_flag_isfalse(flag) ((flag) == 0)

#define OPIUM_CHUNK_SIZE sizeof(opium_uintptr_t)

struct opium_log_s;
struct opium_list_head_s;
struct opium_slab_s;
struct opium_arena_s;
struct opium_rbt_s;
struct opium_cycle_s;

typedef struct opium_log_s         opium_log_t;
typedef struct opium_list_head_s   opium_list_head_t;
typedef struct opium_slab_s        opium_slab_t;
typedef struct opium_arena_s       opium_arena_t;
typedef struct opium_rbt_s         opium_rbt_t;
typedef struct opium_cycle_s       opium_cycle_t;

#include "opium_log.h"
#include "opium_alloc.h"
#include "opium_signals.h"
#include "opium_list.h"
#include "opium_hashfuncs.h"
#include "opium_string.h"
#include "opium_slab.h"
#include "opium_arena.h"
#include "opium_rbt.h"

#define opium_min(a,b) ((a) < (b) ? (a) : (b))
#define opium_max(a,b) ((a) > (b) ? (a) : (b))

#ifdef __cplusplus
extern "C" {
#endif

void opium_cpuinfo(void);

#ifdef __cplusplus
}
#endif

#endif /* OPIUM_CORE_INCLUDE_H */
