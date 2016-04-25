#ifndef ORION_COMPUTE2D_DISCRIM_H
#define ORION_COMPUTE2D_DISCRIM_H 1

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
void orion_compute2D_DiscrimantFunction(
		orion_segmentation_param* param,
		orion_features* features,
		array_int* instance_indices,
		orion_discriminant_function* discrim
		);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_COMPUTE2D_DISCRIM_H */
