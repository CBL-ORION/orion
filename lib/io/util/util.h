#ifndef IO_UTIL_UTIL_H
#define IO_UTIL_UTIL_H 1

#include <stdio.h>

#include "container/array.h"

extern int orion_freadline(FILE* fh, char* buffer);
extern array_int* orion_parse_sequence_int(const char* buffer, array_int** arr_ptr);
extern array_float* orion_parse_sequence_float(const char* buffer, array_float** arr_ptr);

#endif /* IO_UTIL_UTIL_H */
