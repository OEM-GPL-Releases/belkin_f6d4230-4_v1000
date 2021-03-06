#ifndef APR_H
#define APR_H

/**
 * @file include/apr.h
 * @brief APR APR Main Include
 */
/**
 * @defgroup APR APR Routines
 * @{
 */

/* So that we can use inline on some critical functions, and use
 * GNUC attributes (such as to get -Wall warnings for printf-like
 * functions).  Only do this in gcc 2.7 or later ... it may work
 * on earlier stuff, but why chance it.
 *
 * We've since discovered that the gcc shipped with NeXT systems
 * as "cc" is completely broken.  It claims to be __GNUC__ and so
 * on, but it doesn't implement half of the things that __GNUC__
 * means.  In particular it's missing inline and the __attribute__
 * stuff.  So we hack around it.  PR#1613. -djg
 */
#if !defined(__GNUC__) || __GNUC__ < 2 || \
    (__GNUC__ == 2 && __GNUC_MINOR__ < 7) ||\
    defined(NEXT)
#define APR_INLINE
#define __attribute__(__x)
#define APR_HAS_INLINE		0
#else
#define APR_INLINE __inline__
#define APR_HAS_INLINE		1
#endif

#define APR_HAVE_ARPA_INET_H     1
#define APR_HAVE_CONIO_H         0
#define APR_HAVE_CRYPT_H         1
#define APR_HAVE_CTYPE_H         1
#define APR_HAVE_DIRENT_H        1
#define APR_HAVE_ERRNO_H         1
#define APR_HAVE_FCNTL_H         1
#define APR_HAVE_IO_H            0
#define APR_HAVE_LIMITS_H        1
#define APR_HAVE_NETDB_H         1
#define APR_HAVE_NETINET_IN_H    1
#define APR_HAVE_NETINET_TCP_H   1
#define APR_HAVE_PTHREAD_H       1
#define APR_HAVE_SEMAPHORE_H     1
#define APR_HAVE_SIGNAL_H        1
#define APR_HAVE_STDARG_H        1
#define APR_HAVE_STDINT_H        0
#define APR_HAVE_STDIO_H         1
#define APR_HAVE_STDLIB_H        1
#define APR_HAVE_STRING_H        1
#define APR_HAVE_STRINGS_H       1
#define APR_HAVE_SYS_SENDFILE_H  1
#define APR_HAVE_SYS_SIGNAL_H    1
#define APR_HAVE_SYS_SOCKET_H    1
#define APR_HAVE_SYS_SYSLIMITS_H 0
#define APR_HAVE_SYS_TIME_H      1
#define APR_HAVE_SYS_TYPES_H     1
#define APR_HAVE_SYS_UIO_H       1
#define APR_HAVE_SYS_UN_H        1
#define APR_HAVE_SYS_WAIT_H      1
#define APR_HAVE_TIME_H          1
#define APR_HAVE_UNISTD_H        1

#define APR_HAVE_SHMEM_MMAP_TMP     1
#define APR_HAVE_SHMEM_MMAP_SHM     0
#define APR_HAVE_SHMEM_MMAP_ZERO    0
#define APR_HAVE_SHMEM_SHMGET_ANON  1
#define APR_HAVE_SHMEM_SHMGET       1
#define APR_HAVE_SHMEM_MMAP_ANON    1
#define APR_HAVE_SHMEM_BEOS         0

#define APR_USE_SHMEM_MMAP_TMP     0
#define APR_USE_SHMEM_MMAP_SHM     0
#define APR_USE_SHMEM_MMAP_ZERO    0
#define APR_USE_SHMEM_SHMGET_ANON  0
#define APR_USE_SHMEM_SHMGET       1
#define APR_USE_SHMEM_MMAP_ANON    1
#define APR_USE_SHMEM_BEOS         0

#define APR_USE_FLOCK_SERIALIZE           0 
#define APR_USE_SYSVSEM_SERIALIZE         1
#define APR_USE_POSIXSEM_SERIALIZE        0
#define APR_USE_FCNTL_SERIALIZE           0
#define APR_USE_PROC_PTHREAD_SERIALIZE    0 
#define APR_USE_PTHREAD_SERIALIZE         1 

#define APR_HAS_FLOCK_SERIALIZE           1
#define APR_HAS_SYSVSEM_SERIALIZE         1
#define APR_HAS_POSIXSEM_SERIALIZE        0
#define APR_HAS_FCNTL_SERIALIZE           1
#define APR_HAS_PROC_PTHREAD_SERIALIZE    0
#define APR_HAS_RWLOCK_SERIALIZE          0

#define APR_PROCESS_LOCK_IS_GLOBAL        0

#define APR_HAVE_CORKABLE_TCP   1 
#define APR_HAVE_GETRLIMIT      1
#define APR_HAVE_IN_ADDR        1
#define APR_HAVE_INET_ADDR      1
#define APR_HAVE_INET_NETWORK   1
#define APR_HAVE_IPV6           1
#define APR_HAVE_MEMMOVE        1
#define APR_HAVE_SETRLIMIT      1
#define APR_HAVE_SIGACTION      1
#define APR_HAVE_SIGSUSPEND     1
#define APR_HAVE_SIGWAIT        1
#define APR_HAVE_STRCASECMP     1
#define APR_HAVE_STRDUP         1
#define APR_HAVE_STRICMP        0
#define APR_HAVE_STRNCASECMP    1
#define APR_HAVE_STRNICMP       0
#define APR_HAVE_STRSTR         1
#define APR_HAVE_MEMCHR         1
#define APR_HAVE_STRUCT_RLIMIT  0
#define APR_HAVE_UNION_SEMUN    0

#if APR_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#if APR_HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

#if APR_HAVE_STDINT_H
#include <stdint.h>
#endif

/*  APR Feature Macros */
#define APR_HAS_SHARED_MEMORY     1
#define APR_HAS_THREADS           1
#define APR_HAS_SENDFILE          1
#define APR_HAS_MMAP              1
#define APR_HAS_FORK              1
#define APR_HAS_RANDOM            1
#define APR_HAS_OTHER_CHILD       1
#define APR_HAS_DSO               1
#define APR_HAS_SO_ACCEPTFILTER   0
#define APR_HAS_UNICODE_FS        0
#define APR_HAS_PROC_INVOKED      0
#define APR_HAS_USER              1
#define APR_HAS_LARGE_FILES       0
#define APR_HAS_XTHREAD_FILES     0
#define APR_HAS_OS_UUID           0

/* APR sets APR_FILES_AS_SOCKETS to 1 on systems where it is possible
 * to poll on files/pipes.  On such a system, the application can
 * call apr_socket_from_file() to get an APR socket representation and 
 * then pass the socket representation to apr_poll_socket_add().
 */
#define APR_FILES_AS_SOCKETS      1

/* Not all platforms have a real INADDR_NONE.  This macro replaces INADDR_NONE
 * on all platforms.
 */
#define APR_INADDR_NONE           INADDR_NONE

/* This macro indicates whether or not EBCDIC is the native character set.
 */
#define APR_CHARSET_EBCDIC        0

/* If we have a TCP implementation that can be "corked", what flag
 * do we use?
 */
#define APR_TCP_NOPUSH_FLAG       TCP_CORK

/* Is the TCP_NODELAY socket option inherited from listening sockets?
*/
#define APR_TCP_NODELAY_INHERITED 1

/* Is the O_NONBLOCK flag inherited from listening sockets?
*/
#define APR_O_NONBLOCK_INHERITED 1

/* Typedefs that APR needs. */

typedef  unsigned char           apr_byte_t;

typedef  short           apr_int16_t;
typedef  unsigned short  apr_uint16_t;
                                               
typedef  int             apr_int32_t;
typedef  unsigned int    apr_uint32_t;
                                               
typedef  long long            apr_int64_t;
typedef  unsigned long long   apr_uint64_t;

typedef  size_t          apr_size_t;
typedef  ssize_t         apr_ssize_t;
typedef  off_t           apr_off_t;
typedef  socklen_t       apr_socklen_t;

/* Mechanisms to properly type numeric literals */
#define APR_INT64_C(val) (val##LL)


/* Definitions that APR programs need to work properly. */

#define APR_THREAD_FUNC

/**
 * APR_DECLARE_EXPORT is defined when building the APR dynamic library,
 * so that all public symbols are exported.
 *
 * APR_DECLARE_STATIC is defined when including the APR public headers,
 * to provide static linkage when the dynamic library may be unavailable.
 *
 * APR_DECLARE_STATIC and APR_DECLARE_EXPORT are left undefined when
 * including the APR public headers, to import and link the symbols from the 
 * dynamic APR library and assure appropriate indirection and calling 
 * conventions at compile time.
 */

/**
 * The public APR functions are declared with APR_DECLARE(), so they may
 * use the most appropriate calling convention.  Public APR functions with 
 * variable arguments must use APR_DECLARE_NONSTD().
 *
 * @deffunc APR_DECLARE(rettype) apr_func(args);
 */
#define APR_DECLARE(type)            type

/**
 * The public APR functions using variable arguments are declared with 
 * AP_DECLARE(), as they must use the C language calling convention.
 *
 * @deffunc APR_DECLARE_NONSTD(rettype) apr_func(args, ...);
 */
#define APR_DECLARE_NONSTD(type)     type

/**
 * The public APR variables are declared with AP_MODULE_DECLARE_DATA.
 * This assures the appropriate indirection is invoked at compile time.
 *
 * @deffunc APR_DECLARE_DATA type apr_variable;
 * @tip APR_DECLARE_DATA extern type apr_variable; syntax is required for
 * declarations within headers to properly import the variable.
 */
#define APR_DECLARE_DATA

/* Define APR_SSIZE_T_FMT.  
 * If ssize_t is an integer we define it to be "d",
 * if ssize_t is a long int we define it to be "ld",
 * if ssize_t is neither we declare an error here.
 * I looked for a better way to define this here, but couldn't find one, so
 * to find the logic for this definition search for "ssize_t_fmt" in
 * configure.in.
 */
#define APR_SSIZE_T_FMT "d"

/* And APR_SIZE_T_FMT */
#define APR_SIZE_T_FMT "d"

/* And APR_OFF_T_FMT */
#define APR_OFF_T_FMT "ld"

/* And APR_PID_T_FMT */
#define APR_PID_T_FMT "d"

/* And APR_INT64_T_FMT */
#define APR_INT64_T_FMT "lld"
#define APR_INT64_T_FMT_LEN 3

/* Deal with atoi64 variables ... these should move to apr_private.h */
#define APR_HAVE_INT64_STRFN  1
#define APR_INT64_STRFN	      strtoll

/* are we going to force the generic atomic operations */
#define APR_FORCE_ATOMIC_GENERIC 1

/* Does the proc mutex lock threads too */
#define APR_PROC_MUTEX_IS_GLOBAL      0

/* Local machine definition for console and log output. */
#define APR_EOL_STR              "\n"

#if APR_HAVE_SYS_WAIT_H

/* We have a POSIX wait interface */
#include <sys/wait.h>

#ifdef WEXITSTATUS
#define apr_wait_t       int
#else
#define apr_wait_t       union wait
#define WEXITSTATUS(status)    (int)((status).w_retcode)
#define WTERMSIG(status)       (int)((status).w_termsig)
#endif /* !WEXITSTATUS */
#endif /* HAVE_SYS_WAIT_H */

#ifdef OS2
#define INCL_DOS
#define INCL_DOSERRORS
#include <os2.h>
#endif

/* header files for PATH_MAX, _POSIX_PATH_MAX */
#if APR_HAVE_SYS_SYSLIMITS_H
#include <sys/syslimits.h>
#endif
#if APR_HAVE_LIMITS_H
#include <limits.h>
#endif

#if defined(PATH_MAX)
#define APR_PATH_MAX       PATH_MAX
#elif defined(_POSIX_PATH_MAX)
#define APR_PATH_MAX       _POSIX_PATH_MAX
#else
#error no decision has been made on APR_PATH_MAX for your platform
#endif
/** @} */
#endif /* APR_H */
