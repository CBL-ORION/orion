/* TODO
 *
 * Refactor: computeFeatures
 */
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeFeatures.h"

#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeEigenvaluesGaussianFilter.h"

vector_float* orion_computeFeatures( orion_segmentation_param* param, ndarray3* vol ) {
	orion_eigenvalue_feature_method eig_method = EIG_FEAT_METHOD_SORT_FRANGI;
	array_orion_eig_feat_result* r =
		orion_computeEigenvaluesGaussianFilter(vol, eig_method, param->apply_log, param->scales );

	/*
	 * EXTRACTING THE FEATURE VECTORS
	 *
	 * - Sorting of the eigenvalues according to Frangi --- |Lambda_1| <= |Lambda_2| <= |Lambda_3|
	 *
	 * - Sorting of the eigenvalues according to Sato --     Lambda_3  <= Lambda_2   <= Lambda_1
	 */

	WARN_UNIMPLEMENTED;
}
