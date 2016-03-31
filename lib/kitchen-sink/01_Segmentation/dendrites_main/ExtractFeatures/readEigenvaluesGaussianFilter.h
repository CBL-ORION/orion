#ifndef ORION_READ_EIGEN_GAUSS_H
#define ORION_READ_EIGEN_GAUSS_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/array_eig_feat_result.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/multiscaleLaplacianFilter.h"
#include "segmentation/orion_features.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern
orion_features* orion_readEigenvaluesGaussianFilter(
		array_orion_eig_feat_result* eigen,
		orion_multiscale_laplacian_output* laplacian_result );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_READ_EIGEN_GAUSS_H */
