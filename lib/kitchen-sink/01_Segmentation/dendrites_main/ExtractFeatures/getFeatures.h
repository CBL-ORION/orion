#ifndef ORION_GET_FEATURES_H
#define ORION_GET_FEATURES_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "ndarray/ndarray3.h"
#include "container/vector.h"
#include "param/segmentation.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/multiscaleLaplacianFilter.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeFeatures.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern
orion_features* orion_getFeatures(
		orion_segmentation_param* param,
		ndarray3* vol,
		orion_multiscale_laplacian_output* laplacian_result );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_GET_FEATURES_H */
