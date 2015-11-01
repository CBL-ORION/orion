/* TODO
 *
 * Refactor: getFeatures
 */
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/getFeatures.h"

#include "simple-log/simplelog.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeFeatures.h"

vector_float* orion_getFeatures( orion_segmentation_param* param, ndarray3* vol ) {
	LOG_INFO("Computing Eigenvalues of Hessian Matrix...");
	vector_float* feat = orion_computeFeatures(param, vol);
	LOG_INFO("Done computing eigenvalues.");
	return feat;
}
