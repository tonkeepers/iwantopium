#ifndef OPIUM_MODULE_TYPES_INCLUDED_H
#define OPIUM_MODULE_TYPES_INCLUDED_H

/* ========== SYSTEM DETECTION ========== */
#ifdef __linux__
#define OPIUM_LINUX    1
#define OPIUM_POSIX    1
#elif _WIN32
#define OPIUM_WINDOWS  1
#elif __APPLE__
#define OPIUM_MACOS    1
#define OPIUM_POSIX    1
#elif __FreeBSD__
#define OPIUM_BSD      1
#define OPIUM_POSIX    1
#else
#error "Unsupported operating system"
#endif

/* ========== CRITICAL TYPES ========== */
/* These types are visible EVERYWHERE in the codebase */
/* Cannot be hidden behind vtable - must be defined once */

/* File descriptor / handle */
#ifdef OPIUM_WINDOWS
#include <windows.h>
typedef HANDLE          opium_fd_t;
#define OPIUM_INVALID_FD INVALID_HANDLE_VALUE
#else
typedef int             opium_fd_t;
#define OPIUM_INVALID_FD (-1)
#endif

/* Process ID */
#ifdef OPIUM_WINDOWS
typedef DWORD           opium_pid_t;
#define OPIUM_INVALID_PID 0
#else
#include <unistd.h>
typedef pid_t           opium_pid_t;
#define OPIUM_INVALID_PID (0)
#endif

/* Socket handle (differs from file descriptor on Windows) */
#ifdef OPIUM_WINDOWS
#include <winsock2.h>
typedef SOCKET          opium_socket_t;
#define OPIUM_INVALID_SOCKET INVALID_SOCKET
#else
typedef int             opium_socket_t;
#define OPIUM_INVALID_SOCKET (-1)
#endif

/* OFFSET */
#ifdef OPIUM_WINDOWS
#include <winsock2.h>
typedef SOCKET          opium_socket_t;
#define OPIUM_INVALID_SOCKET INVALID_SOCKET
#else
typedef __off_t         opium_off_t;
#define OPIUM_INVALID_SOCKET (-1)
#endif

/* Memory size (platform independent) */
#include <stddef.h>
#include <stdint.h>
typedef size_t             opium_size_t;
typedef uintptr_t          opium_uintptr_t;
typedef intptr_t           opium_intptr_t;

/* Generic pointer for vtable callbacks */
typedef void*              opium_ptr_t;
typedef const void*        opium_const_ptr_t;

/* Boolean type */
#include <stdbool.h>
typedef bool               opium_bool_t;

/* Error codes */
typedef int                opium_err_t;

/* ========== COMPILER ATTRIBUTES ========== */
/* For inlining, alignment, etc. */
#ifdef __GNUC__
#define OPIUM_INLINE        static inline __attribute__((always_inline))
#define OPIUM_NOINLINE      __attribute__((noinline))
#define OPIUM_PACKED        __attribute__((packed))
#define OPIUM_ALIGNED(n)    __attribute__((aligned(n)))
#define OPIUM_PRINTF(fmt, args) __attribute__((format(printf, fmt, args)))
#elif _MSC_VER
#define OPIUM_INLINE        static __forceinline
#define OPIUM_NOINLINE      __declspec(noinline)
#define OPIUM_PACKED
#define OPIUM_ALIGNED(n)    __declspec(align(n))
#define OPIUM_PRINTF(fmt, args)
#else
#define OPIUM_INLINE        static inline
#define OPIUM_NOINLINE
#define OPIUM_PACKED
#define OPIUM_ALIGNED(n)
#define OPIUM_PRINTF(fmt, args)
#endif

/* ========== BRANCH PREDICTION ========== */
#ifdef __GNUC__
#define opium_likely(x)     __builtin_expect(!!(x), 1)
#define opium_unlikely(x)   __builtin_expect(!!(x), 0)
#else
#define opium_likely(x)     (x)
#define opium_unlikely(x)   (x)
#endif

/* ========== ASSERTIONS ========== */
#ifdef OPIUM_DEBUG
#include <assert.h>
#define OPIUM_ASSERT(expr)  assert(expr)
#define OPIUM_STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)
#else
#define OPIUM_ASSERT(expr)  ((void)0)
#define OPIUM_STATIC_ASSERT(expr, msg) ((void)0)
#endif

#endif /* OPIUM_MODULE_TYPES_INCLUDED_H */
