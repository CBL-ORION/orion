#ifndef CONFIG_PLATFORM_H
#define CONFIG_PLATFORM_H 1

/* define OS_* macros */
#if defined(_WIN32)
  #define OS_WINDOWS 1
#else
  #define OS_UNIX 1
#endif


/* Platform specific settings */

/* On Windows */
#if OS_WINDOWS
  #if _MSC_VER && !__INTEL_COMPILER
    /* Microsoft compiler */

    /* needed for the secure rand_s function */
    #define _CRT_RAND_S 1
    #include <stdlib.h>

  #endif

  /* the extension used for executables */
  #ifndef PLATFORM_EXE_EXT
    #define PLATFORM_EXE_EXT ".exe"
  #endif /* PLATFORM_EXE_EXT */

#endif /* OS_WINDOWS */

#if OS_UNIX

  /* the extension used for executables */
  #ifndef PLATFORM_EXE_EXT
    #define PLATFORM_EXE_EXT ""
  #endif /* PLATFORM_EXE_EXT */

#endif /* OS_UNIX */

#endif /* CONFIG_PLATFORM_H */
