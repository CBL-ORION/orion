#ifndef PARAM_PARAM_H
#define PARAM_PARAM_H 1

#include "container/array.h"

typedef struct {
	array_float* scales;
	char* input_filename;
	char* output_filename;
} orion_parameters;

extern orion_parameters* orion_parameters_new();
extern void orion_parameters_free(orion_parameters* param);

#endif /* PARAM_PARAM_H */
