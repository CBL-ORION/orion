#ifndef ORION_FEATURES_H
#define ORION_FEATURES_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "container/vector.h"

/* structs, enums */
#define ORION_NUMBER_OF_SEGMENTATION_FEATURES 2

typedef struct {
	/*
	 * There are two features
	 *
	 * features[0]: The 2nd eigenvalue of the Gaussian filter.
	 *
	 * features[1]: The 3rd eigenvalue of the Gaussian filter.
	 */
	size_t number_of_features;
	vector_float* features[ORION_NUMBER_OF_SEGMENTATION_FEATURES];
	size_t number_of_instances;
} orion_features;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern orion_features* orion_features_new( size_t instances );
extern void orion_features_free( orion_features* f );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_FEATURES_H */
