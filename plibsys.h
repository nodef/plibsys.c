#pragma once
#include "plibsys/plibsys.h"


#ifdef PLIBSYS_IMPLEMENTATION

/* Include platform-independent core implementations */
#include "plibsys/perror.c"
#include "plibsys/pfile.c"
#include "plibsys/phashtable.c"
#include "plibsys/pinifile.c"
#include "plibsys/pipc.c"
#include "plibsys/plist.c"
#include "plibsys/pmain.c"
#include "plibsys/pmem.c"
#include "plibsys/pprocess.c"
#include "plibsys/pstring.c"

/* Include all cryptographic hash implementations (platform-independent) */
#include "plibsys/pcryptohash-gost3411.c"
#include "plibsys/pcryptohash-md5.c"
#include "plibsys/pcryptohash-sha1.c"
#include "plibsys/pcryptohash-sha2-256.c"
#include "plibsys/pcryptohash-sha2-512.c"
#include "plibsys/pcryptohash-sha3.c"
#include "plibsys/pcryptohash.c"

/* Include all tree implementations (platform-independent) */
#include "plibsys/ptree-avl.c"
#include "plibsys/ptree-bst.c"
#include "plibsys/ptree-rb.c"
#include "plibsys/ptree.c"

/* Platform-specific: Atomic operations */
#if defined(P_CC_MSVC) || defined(P_CC_BORLAND)
#include "plibsys/patomic-win.c"
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) &&            \
    !defined(P_CC_PGI)
/* C11 atomics */
#include "plibsys/patomic-c11.c"
#elif (defined(P_CC_GNU) &&                                                    \
    (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))) ||               \
    (defined(P_CC_INTEL) && __INTEL_COMPILER >= 1110) ||                       \
    (defined(P_CC_CLANG) && __clang_major__ >= 3)
/* GCC/Clang __sync builtins */
#include "plibsys/patomic-sync.c"
#elif defined(P_CC_DEC) && defined(__alpha)
/* DEC Alpha compiler */
#include "plibsys/patomic-decc.c"
#else
/* Simulation fallback */
#include "plibsys/patomic-sim.c"
#endif /* P_CC_MSVC */

/* Platform-specific: Spinlock */
#if defined(P_CC_MSVC) || defined(P_CC_BORLAND)
#include "plibsys/pspinlock-win.c"
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) &&            \
    !defined(P_CC_PGI)
/* C11 atomics */
#include "plibsys/pspinlock-c11.c"
#elif (defined(P_CC_GNU) &&                                                    \
    (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))) ||               \
    (defined(P_CC_INTEL) && __INTEL_COMPILER >= 1110) ||                       \
    (defined(P_CC_CLANG) && __clang_major__ >= 3)
/* GCC/Clang __sync builtins */
#include "plibsys/pspinlock-sync.c"
#elif defined(P_CC_DEC) && defined(__alpha)
/* DEC Alpha compiler */
#include "plibsys/pspinlock-decc.c"
#else
/* Simulation fallback */
#include "plibsys/pspinlock-sim.c"
#endif /* P_CC_MSVC */

/* Platform-specific: Mutex */
#if defined(P_OS_WIN)
#include "plibsys/pmutex-win.c"
#elif defined(P_OS_BEOS)
#include "plibsys/pmutex-beos.c"
#elif defined(P_OS_AMIGA)
#include "plibsys/pmutex-amiga.c"
#elif defined(P_OS_ATHEOS)
#include "plibsys/pmutex-atheos.c"
#elif defined(P_OS_OS2)
#include "plibsys/pmutex-os2.c"
#elif defined(P_OS_SOLARIS)
#include "plibsys/pmutex-solaris.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
#include "plibsys/pmutex-posix.c"
#else
#include "plibsys/pmutex-none.c"
#endif /* P_OS_WIN */

/* Platform-specific: Condition Variable */
#if defined(P_OS_WIN)
#include "plibsys/pcondvariable-win.c"
#elif defined(P_OS_BEOS)
#include "plibsys/pcondvariable-beos.c"
#elif defined(P_OS_AMIGA)
#include "plibsys/pcondvariable-amiga.c"
#elif defined(P_OS_ATHEOS)
#include "plibsys/pcondvariable-atheos.c"
#elif defined(P_OS_OS2)
#include "plibsys/pcondvariable-os2.c"
#elif defined(P_OS_SOLARIS)
#include "plibsys/pcondvariable-solaris.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
#include "plibsys/pcondvariable-posix.c"
#else
#include "plibsys/pcondvariable-none.c"
#endif /* P_OS_WIN */

/* Platform-specific: Read-Write Lock */
#if defined(P_OS_WIN)
#include "plibsys/prwlock-win.c"
#elif defined(P_OS_SOLARIS)
#include "plibsys/prwlock-solaris.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
#include "plibsys/prwlock-posix.c"
#else
/* General implementation using mutex + condvar */
#include "plibsys/prwlock-general.c"
#endif /* P_OS_WIN */

/* Platform-specific: Thread */
#if defined(P_OS_WIN)
#include "plibsys/puthread-win.c"
#elif defined(P_OS_BEOS)
#include "plibsys/puthread-beos.c"
#elif defined(P_OS_AMIGA)
#include "plibsys/puthread-amiga.c"
#elif defined(P_OS_ATHEOS)
#include "plibsys/puthread-atheos.c"
#elif defined(P_OS_OS2)
#include "plibsys/puthread-os2.c"
#elif defined(P_OS_SOLARIS)
#include "plibsys/puthread-solaris.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
#include "plibsys/puthread-posix.c"
#else
#include "plibsys/puthread-none.c"
#endif /* P_OS_WIN */

/* Always include the main thread wrapper */
#include "plibsys/puthread.c"

/* Platform-specific: Semaphore */
#if defined(P_OS_WIN)
#include "plibsys/psemaphore-win.c"
#elif defined(P_OS_AMIGA)
#include "plibsys/psemaphore-amiga.c"
#elif defined(P_OS_OS2)
#include "plibsys/psemaphore-os2.c"
#elif defined(P_OS_SOLARIS) || defined(P_OS_IRIX) || defined(P_OS_TRU64) ||    \
    defined(P_OS_UNIXWARE)
/* System V semaphores */
#include "plibsys/psemaphore-sysv.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
/* POSIX semaphores */
#include "plibsys/psemaphore-posix.c"
#else
#include "plibsys/psemaphore-none.c"
#endif /* P_OS_WIN */

/* Platform-specific: Shared Memory */
#if defined(P_OS_WIN)
#include "plibsys/pshm-win.c"
#elif defined(P_OS_AMIGA)
#include "plibsys/pshm-amiga.c"
#elif defined(P_OS_OS2)
#include "plibsys/pshm-os2.c"
#elif defined(P_OS_SOLARIS) || defined(P_OS_IRIX) || defined(P_OS_TRU64) ||    \
    defined(P_OS_UNIXWARE)
/* System V shared memory */
#include "plibsys/pshm-sysv.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
/* POSIX shared memory */
#include "plibsys/pshm-posix.c"
#else
#include "plibsys/pshm-none.c"
#endif /* P_OS_WIN */

/* Shared memory buffer (platform-independent wrapper) */
#include "plibsys/pshmbuffer.c"

/* Platform-specific: Directory operations */
#if defined(P_OS_WIN)
#include "plibsys/pdir-win.c"
#elif defined(P_OS_OS2)
#include "plibsys/pdir-os2.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
#include "plibsys/pdir-posix.c"
#else
#include "plibsys/pdir-none.c"
#endif /* P_OS_WIN */

/* Directory wrapper (platform-independent) */
#include "plibsys/pdir.c"

/* Platform-specific: Library Loader */
#if defined(P_OS_WIN)
#include "plibsys/plibraryloader-win.c"
#elif defined(P_OS_BEOS)
#include "plibsys/plibraryloader-beos.c"
#elif defined(P_OS_AMIGA)
#include "plibsys/plibraryloader-amiga.c"
#elif defined(P_OS_OS2)
#include "plibsys/plibraryloader-os2.c"
#elif defined(P_OS_HPUX)
/* HP-UX uses shl_load */
#include "plibsys/plibraryloader-shl.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
/* POSIX dlopen */
#include "plibsys/plibraryloader-posix.c"
#else
#include "plibsys/plibraryloader-none.c"
#endif /* P_OS_WIN */

/* Platform-specific: Time Profiler */
#if defined(P_OS_WIN)
#include "plibsys/ptimeprofiler-win.c"
#elif defined(P_OS_BEOS)
#include "plibsys/ptimeprofiler-beos.c"
#elif defined(P_OS_AMIGA)
#include "plibsys/ptimeprofiler-amiga.c"
#elif defined(P_OS_OS2)
#include "plibsys/ptimeprofiler-os2.c"
#elif defined(P_OS_MAC) || defined(P_OS_DARWIN)
/* Mach absolute time */
#include "plibsys/ptimeprofiler-mach.c"
#elif defined(P_OS_SOLARIS)
/* Solaris gethrtime() */
#include "plibsys/ptimeprofiler-solaris.c"
#elif defined(P_OS_UNIX)
/* POSIX clock_gettime() */
#include "plibsys/ptimeprofiler-posix.c"
#else
/* Generic gettimeofday() fallback */
#include "plibsys/ptimeprofiler-generic.c"
#endif /* P_OS_WIN */

/* Time profiler wrapper (platform-independent) */
#include "plibsys/ptimeprofiler.c"

/* Platform-specific: System close-on-exec */
#if defined(P_OS_WIN)
#include "plibsys/psysclose-win.c"
#elif defined(P_OS_DARWIN) || defined(P_OS_MAC)
#include "plibsys/psysclose-darwin.c"
#elif defined(P_OS_UNIX) || defined(P_OS_CYGWIN) || defined(P_OS_MSYS)
#include "plibsys/psysclose-unix.c"
#endif /* P_OS_WIN */

/* Network sockets (platform-independent, but uses platform headers) */
#include "plibsys/psocket.c"
#include "plibsys/psocketaddress.c"
#if defined(P_OS_WIN)
#pragma comment(lib, "ws2_32.lib")
#endif /* P_OS_WIN */

#endif /* PLIBSYS_IMPLEMENTATION */
