#ifndef ORION_REMOVE_ISOLATED_REZ_H
#define ORION_REMOVE_ISOLATED_REZ_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "segmentation/orion_discriminant.h"
#include "container/array.h"
#include "segmentation/orion_features.h"
#include "param/segmentation.h"

/* structs, enums */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern
void orion_removeIsolatedResponses(
		orion_segmentation_param* param,
		orion_features*  features,
		orion_discriminant_function* discrim,
		array_int* sample_instance_indices,
		array_int** non_isolated_instance_indices
		);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_REMOVE_ISOLATED_REZ_H */
