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

/* TODO document */
#define orion_histogram_elems( discrim ) ( discrim->m * discrim->n )

#define _orion_histogram_index(discrim, bin_m, bin_n) (bin_m * discrim->m + bin_n)

/* TODO document */
#define orion_histogram_increment(discrim, bin_m, bin_n) \
	( ++( discrim->histogram[ _orion_histogram_index(discrim, bin_m, bin_n)  ] ) )

typedef struct {
	size_t m; /* number of bins in the first dimension */
	size_t n; /* number of bins in the second dimension */
	size_t* histogram; /* dimensions: [m, n] */


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
extern void orion_histogram_init(orion_discriminant_function* discrim, size_t m, size_t n);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_DISCRIMINANT_H */
