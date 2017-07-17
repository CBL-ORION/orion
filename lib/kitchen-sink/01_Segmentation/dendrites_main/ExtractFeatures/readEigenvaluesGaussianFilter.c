#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/readEigenvaluesGaussianFilter.h"

#include <math.h>

/* TODO
 *
 * Returns a feature vector for every training instance.
 *
 * Uses the multiscale Laplacian response to choose the appropriate scale.
 *
 * Filters out NaN values in the feature vector.
 *
 * Refactor: readEigenvaluesGaussianFilter
 */
orion_features* orion_readEigenvaluesGaussianFilter(
		array_orion_eig_feat_result* eigen,
		orion_multiscale_laplacian_output* laplacian_result ) {

	orion_features* feat;

	/* only keep the 2nd and 3rd eigenvalues */
	orion_eig_feat_result* result_first_scale
		= array_get_orion_eig_feat_result( eigen, 0 );

	ndarray3* result_first_scale_first_eig
		= array_get_ndarray3( result_first_scale->eig_feat, 0 );

	size_t feat_instances = ndarray3_elems(result_first_scale_first_eig);

	feat = orion_features_new( feat_instances );

	/* Use the scale index in `laplacian_result` to create a length 2
	 * feature vector for every training pixel.
	 *
	 * The features are the 2nd and 3rd eigenvalues at the maximal
	 * Laplacian response scale.
	 */
	for( int n_idx = 0; n_idx < feat_instances; n_idx++ ) {
		size_t scale_idx = (size_t)( laplacian_result->max_response_at_scale_idx->p[n_idx] );

		orion_eig_feat_result* scale_result
			= array_get_orion_eig_feat_result( eigen, scale_idx );

		/* get the 2nd eigenvalue (at index 1) */
		pixel_type eig_2nd = array_get_ndarray3( scale_result->eig_feat, 1 )->p[n_idx];

		/* get the 3rd eigenvalue (at index 2) */
		pixel_type eig_3rd = array_get_ndarray3( scale_result->eig_feat, 2 )->p[n_idx];

		/* If NaN, then replace with zero.
		 *
		 * This is to prevent NaN propagation in other calculations.
		 */
		if( isnan(eig_2nd) ) { eig_2nd = 0; }
		if( isnan(eig_3rd) ) { eig_3rd = 0; }

		/* store in feature vector */
		vector_set_float( feat->features[0], n_idx, eig_2nd );
		vector_set_float( feat->features[1], n_idx, eig_3rd );
	}

	return feat;
}
