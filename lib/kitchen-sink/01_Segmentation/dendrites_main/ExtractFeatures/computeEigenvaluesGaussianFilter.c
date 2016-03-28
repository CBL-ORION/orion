/* TODO
 *
 * Refactor: computeEigenvaluesGaussianFilter
 *
 * NOTE:
 * - This does not split the data into a subvolumes on the disk as it does in
 *   the original MATLAB code.
 * - Applying the log() function should be factored out to another function.
 */

#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeEigenvaluesGaussianFilter.h"
#include "integration/itk/itk.hxx"

/**
 * This function computes eigenvalues after applying various filtering methods
 * for feature extraction. These eigenvalue features are used to measure the
 * vessellness of the data.
 */
array_orion_eig_feat_result* orion_computeEigenvaluesGaussianFilter(
		ndarray3* input_volume,
		orion_eigenvalue_feature_method method,
		bool apply_log,
		array_float* scales
	) {
	/* WISH cache the output for each scale */

	if( apply_log ) {
		die("Please refactor and remove use of apply_log as it is orthogonal to the eigenvalue filtering ( apply_log == %c )", apply_log);
	}

	/* loop over all scales */
	size_t n_scales = array_length_float(scales);
	array_orion_eig_feat_result* all_results = array_new_orion_eig_feat_result(n_scales);
	for( size_t scale_idx = 0; scale_idx < n_scales; scale_idx++ ) {
		orion_eig_feat_result* res = orion_eig_feat_result_new();
		res->scale = array_get_float(scales, scale_idx);

		/* calculate each filter */
		if( method == EIG_FEAT_METHOD_SORT_SATO ) {
			/* call Sato filter */
			res->eig_feat = orion_filter_method_sato(input_volume, res->scale);
		} else if( method == EIG_FEAT_METHOD_SORT_FRANGI ) {
			/* call Frangi filter */
			res->eig_feat = orion_filter_method_frangi(input_volume, res->scale);
		} else if( method == EIG_FEAT_METHOD_SINGLE_VALUE ) {
			/* calculate eigenvalues */
			res->eig_feat = orion_filter_method_single_eigenvalue(input_volume, res->scale);
		} else {
			die("Unknown sort method: %d", method);
		}

		array_add_orion_eig_feat_result( all_results, res );
	}
	return all_results;
}
