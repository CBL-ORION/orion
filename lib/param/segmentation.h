#ifndef PARAM_SEGMENTATION_H
#define PARAM_SEGMENTATION_H 1

#include <stdint.h>

#include "container/array.h"

#define ORION_SEGMENTATION_PERCENTAGE_THRESHOLD_INTENSITY_DEFAULT 0.9
#define ORION_SEGMENTATION_BINS_DEFAULT 500

typedef struct {
	array_float* scales;     /* sigma */
	float percentage_threshold_intensity; /* default: 0.9 */
	size_t number_of_stacks; /* length of volume_names */
	int min_conn_comp_to_remove; /* Used in the multiscale only. */
	uint32_t bins; /* number of bins used to calculate the histogram */
} orion_segmentation_param;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern orion_segmentation_param* orion_segmentation_param_new();
extern void orion_segmentation_param_free(orion_segmentation_param* param);
extern void orion_segmentation_param_set_default_scales( orion_segmentation_param* param );
extern void orion_segmentation_param_dump( orion_segmentation_param* param );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* PARAM_SEGMENTATION_H */
