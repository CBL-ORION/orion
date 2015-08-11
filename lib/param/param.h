#ifndef PARAM_PARAM_H
#define PARAM_PARAM_H 1

#include "container/array.h"

/* TODO restructure this so that the structure has separate parameters for
 * different parts of the pipeline
 *
 * - segmentation
 * - registration
 */
typedef struct {
	array_float* scales;     /* sigma */
	char* input_filename;
	char* output_filename;
} orion_parameters;

extern orion_parameters* orion_parameters_new();
extern void orion_parameters_free(orion_parameters* param);
extern void orion_parameters_set_default_scales( orion_parameters* param );

#endif /* PARAM_PARAM_H */
