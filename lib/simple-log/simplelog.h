#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "util/util.h"

#define SIMPLE_LOG_FILE stderr

extern void LOG_ERROR(const char* message, ...);
extern void LOG_INFO (const char* message, ...);
extern void LOG_DEBUG(const char* message, ...);

#endif /* SIMPLE_LOG_H */
