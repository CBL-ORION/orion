#ifndef PARAM_SEGMENTATION_H
#define PARAM_SEGMENTATION_H 1

#include "container/array.h"

#define ORION_SEGMENTATION_PERCENTAGE_THRESHOLD_INTENSITY_DEFAULT 0.9

typedef struct {
	array_float* scales;     /* sigma */
	float percentage_threshold_intensity;/* default: 0.9 */
	size_t number_of_stacks; /* length of volume_names */
} orion_segmentation_param;

extern orion_segmentation_param* orion_segmentation_param_new();
extern void orion_segmentation_param_free(orion_segmentation_param* param);
extern void orion_segmentation_param_set_default_scales( orion_segmentation_param* param );
extern void orion_segmentation_param_dump( orion_segmentation_param* param );

#endif /* PARAM_SEGMENTATION_H */
