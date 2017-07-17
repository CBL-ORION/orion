#ifndef readNegativeSamples_H
#define readNegativeSamples_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "param/segmentation.h"
#include "container/vector.h"
#include "ndarray/ndarray3.h"
#include "simple-log/simplelog.h"

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/multiscaleLaplacianFilter.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern
orion_multiscale_laplacian_output*
orion_readNegativeSamples(
		orion_segmentation_param* param,
		ndarray3* vol );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* readNegativeSamples_H */
