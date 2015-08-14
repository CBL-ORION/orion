#ifndef PARAM_IO_H
#define PARAM_IO_H 1

#include <stdio.h>
#include "util.h"

typedef struct {
	char* input_filename;
	char* output_filename;
} orion_io_param;

extern orion_io_param* orion_io_param_new();
extern void orion_io_param_free(orion_io_param* param);
extern void orion_io_param_dump( orion_io_param* param );

#endif /* PARAM_IO_H */
