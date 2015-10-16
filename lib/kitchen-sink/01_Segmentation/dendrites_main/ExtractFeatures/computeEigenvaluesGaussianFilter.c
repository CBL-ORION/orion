/* TODO
 *
 * Refactor: computeEigenvaluesGaussianFilter
 *
 * NOTE:
 * - This does not split the data into a subvolumes on the disk as it does in
 *   the original MATLAB code.
 * - Applying the log() function should be factored out to another function.
 */

#include <stdbool.h>

#include "ndarray/ndarray3.h"
#include "ndarray/array_ndarray3.h"
#include "container/array.h"

#include "integration/itk/itk.hxx"

typedef enum {
	EIG_FEAT_METHOD_SORT_SATO = 1,
	EIG_FEAT_METHOD_SORT_FRANGI,
	EIG_FEAT_METHOD_SINGLE_VALUE,

	EIG_FEAT_METHOD_ENUM_FIRST = EIG_FEAT_METHOD_SORT_SATO,
	EIG_FEAT_METHOD_ENUM_LAST = EIG_FEAT_METHOD_SINGLE_VALUE
} orion_eigenvalue_feature_method;

/**
 * This function computes eigenvalues after applying various filtering methods
 * for feature extraction. These eigenvalue features are used to measure the
 * vessellness of the data.
 */
array_ndarray3* orion_computeEigenvaluesGaussianFilter(
		ndarray3* input_volume,
		orion_eigenvalue_feature_method method,
		bool apply_log,
		array_float* scales
	) {
	/* WISH cache the output for each scale */

	if( apply_log ) {
		die("Please refactor and remove use of apply_log as it is orthogonal to the eigenvalue filtering ( apply_log == %c )", apply_log);
	}

	/* TODO calculate each filter */
	/* TODO loop over all scales */
	size_t scale_idx = 0;
	if( method == EIG_FEAT_METHOD_SORT_SATO ) {
		/* TODO call Sato filter */
		orion_filter_method_sato(input_volume, array_get_float(scales, scale_idx));
	} else if( method == EIG_FEAT_METHOD_SORT_FRANGI ) {
		/* TODO call Frangi filter */
		orion_filter_method_frangi(input_volume, array_get_float(scales, scale_idx));
	} else if( method == EIG_FEAT_METHOD_SINGLE_VALUE ) {
		/* TODO calculate eigenvalues */
		orion_filter_method_single_eigenvalue(input_volume, array_get_float(scales, scale_idx));
	} else {
		die("Unknown sort method: %d", method);
	}
}
