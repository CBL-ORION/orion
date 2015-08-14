#ifndef PARAM_PARAM_H
#define PARAM_PARAM_H 1

#include <stdbool.h>
#include "container/array.h"

/* each structure has separate parameters for * different parts of the pipeline
 *
 * - segmentation
 * - registration
 */

#include "param/segmentation.h"
#include "param/registration.h"
#include "param/orion3.h"

typedef struct {
	char* input_filename;
	char* output_filename;
} orion_io_param;

extern orion_io_param* orion_io_param_new();
extern void orion_io_param_free(orion_io_param* param);

#endif /* PARAM_PARAM_H */
