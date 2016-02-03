#ifndef UTIL_UTIL_H
#define UTIL_UTIL_H 1

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "util/float.h"
#include "util/string.h"
#include "util/preprocessor.h"
#include "util/mem.h"

#define SQUARED(x) ( (x) * (x) )

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern void _real_die(const char* msg_fmt, const char* origin, ...);
#ifndef die
#define die(_msg_fmt, ...) _real_die(_msg_fmt, SHOWORIGIN, __VA_ARGS__)
#endif

#ifdef __cplusplus
};
#endif /* __cplusplus */


#endif /* UTIL_UTIL_H */
