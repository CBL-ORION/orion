/* TODO
 *
 * Refactor: computeEigenvaluesGaussianFilter
 */

#include <stdbool.h>

#include "ndarray/ndarray3.h"
#include "ndarray/array_ndarray3.h"
#include "container/array.h"

#include "filter/vesselness/FilterCommon.hxx"
#include "filter/vesselness/FilterCommon.hxx"
#include "filter/vesselness/frangi/EigenFrangi.hxx"
#include "filter/vesselness/sato/EigenSato.hxx"

typedef enum {
	EIG_FEAT_METHOD_SORT_SATO = 1,
	EIG_FEAT_METHOD_SORT_FRANGI,
	EIG_FEAT_METHOD_SINGLE_VALUE,

	EIG_FEAT_METHOD_ENUM_FIRST = EIG_FEAT_METHOD_SORT_SATO,
	EIG_FEAT_METHOD_ENUM_LAST = EIG_FEAT_METHOD_SINGLE_VALUE
} orion_eigenvalue_feature_method;

array_ndarray3* orion_computeEigenvaluesGaussianFilter(
		ndarray3* input_volume,
		orion_eigenvalue_feature_method method,
		bool apply_log,
		array_float* scales
	) {
	/* WISH cache the output for each scale */

	/* TODO calculate each filter */
	if( method == EIG_FEAT_METHOD_SORT_SATO ) {
		/* TODO call Sato filter */
	} else if( method == EIG_FEAT_METHOD_SORT_FRANGI ) {
		/* TODO call Frangi filter */
	} else if( method == EIG_FEAT_METHOD_SINGLE_VALUE ) {
		/* TODO calculate eigenvalues */
	} else {
		die("Unknown sort method: %d", method);
	}
}
