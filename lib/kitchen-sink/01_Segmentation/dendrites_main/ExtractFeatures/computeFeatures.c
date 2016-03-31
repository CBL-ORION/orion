/* Retrieve the feature vectors for the training instances.
 *
 * Refactor: computeFeatures
 */
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeFeatures.h"

#include "container/vector.h"
#include "container/array.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeEigenvaluesGaussianFilter.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/readEigenvaluesGaussianFilter.h"

orion_features* orion_computeFeatures(
		orion_segmentation_param* param,
		ndarray3* vol,
		orion_multiscale_laplacian_output* laplacian_result) {
	/*
	 * The features are the eigenvalues of the Hessian Matrix
	 * Set the parameters Low-pass filter that we want to use.
	 */
	bool filter_isotropic = false;
	array_float* adjusted_scales;
	orion_features* feat;

	pixel_type spacing_0dim = vol->has_spacing ? vol->spacing[0] : 1.0;
	/* only use the first scale if not multiscale */
	size_t number_of_scales = param->multiscale
		? array_length_float( param->scales )
		: 1;

	/* adjust the scales by the spacing of the first dimension */
	adjusted_scales = array_new_float( number_of_scales );
	for( size_t s_idx = 0 ; s_idx < number_of_scales; s_idx++ ) {
		array_set_float( adjusted_scales, s_idx,
			spacing_0dim * array_get_float( param->scales, s_idx )
		);
	}

	array_orion_eig_feat_result* result;
	/* compute the eigenvalues for the given scales */
	if( filter_isotropic ) {
		/* compute the eigenvalues using the Isotropic Low pass filter */
		TODO(Dead code);
		/* TODO Remove this
		 * orion_compute_SecondOrderDerivatives(vol, sigma, 60);
		 */
	} else {
		/* compute the eigenvalues using the Gaussian filter */
		result = orion_computeEigenvaluesGaussianFilter(
				vol,
				EIG_FEAT_METHOD_SORT_FRANGI,
				param->apply_log,
				adjusted_scales );
	}

	/* Turn the result into feature vectors */
	feat = orion_readEigenvaluesGaussianFilter( result, laplacian_result );

	return feat;
}
