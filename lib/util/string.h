#ifndef UTIL_STRING_H
#define UTIL_STRING_H 1

#define ORION_BUFFER_SZ 256
#define SIZE_T_FORMAT_SPEC "%zd"

#include <stddef.h>

extern char* safe_malloc_and_strcpy(char** dest, const char* src);
extern char* safe_malloc_and_strncpy(char** dest, const char* src, size_t len);

#endif /* UTIL_STRING_H */
