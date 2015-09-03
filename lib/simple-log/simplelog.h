#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "util/util.h"

#define SIMPLE_LOG_FILE stderr

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern void LOG_ERROR(const char* message, ...);
extern void LOG_INFO (const char* message, ...);
extern void LOG_DEBUG(const char* message, ...);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* SIMPLE_LOG_H */
