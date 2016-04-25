#ifndef ORION_DISCRIMINANT_H
#define ORION_DISCRIMINANT_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "segmentation/orion_features.h"
#include "container/vector.h"
#include "ndarray/ndarray3.h"

/* structs, enums */
/*TODO(Define struct members)*/
typedef struct {

	ndarray3* histogram; /* dimensions: [m, n, 1] */


	/* store the minimum and maximum value for each feature */
	pixel_type min_value[ORION_NUMBER_OF_SEGMENTATION_FEATURES];
	pixel_type max_value[ORION_NUMBER_OF_SEGMENTATION_FEATURES];
	/* for calculating the step size */
	pixel_type step_size[ORION_NUMBER_OF_SEGMENTATION_FEATURES];

	/* location of bin edges for lookup */
	vector_float* edges[ORION_NUMBER_OF_SEGMENTATION_FEATURES];
} orion_discriminant_function;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */



#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_DISCRIMINANT_H */
