/*
 * Get the Eigenvalues of the Hessian matrix as features.
 *
 * Refactor: getFeatures
 */
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/getFeatures.h"

#include "simple-log/simplelog.h"

orion_features* orion_getFeatures(
		orion_segmentation_param* param,
		ndarray3* vol,
		orion_multiscale_laplacian_output* laplacian_result ) {
	LOG_INFO("Computing Eigenvalues of Hessian Matrix...");
	orion_features* feat = orion_computeFeatures(param, vol, laplacian_result );
	LOG_INFO("Done computing eigenvalues.");
	return feat;
}
