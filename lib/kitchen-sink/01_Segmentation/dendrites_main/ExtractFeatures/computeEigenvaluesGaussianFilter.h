#ifndef ORION_COMPUTEEIGENVALUESGAUSSIANFILTER_H
#define ORION_COMPUTEEIGENVALUESGAUSSIANFILTER_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "ndarray/ndarray3.h"
#include "ndarray/array_ndarray3.h"
#include "array_eig_feat_result.h"
#include "container/array.h"

/* structs, enums */
typedef enum {
	EIG_FEAT_METHOD_SORT_SATO = 1,
	EIG_FEAT_METHOD_SORT_FRANGI,
	EIG_FEAT_METHOD_SINGLE_VALUE,

	EIG_FEAT_METHOD_ENUM_FIRST = EIG_FEAT_METHOD_SORT_SATO,
	EIG_FEAT_METHOD_ENUM_LAST = EIG_FEAT_METHOD_SINGLE_VALUE
} orion_eigenvalue_feature_method;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern array_orion_eig_feat_result* orion_computeEigenvaluesGaussianFilter(
		ndarray3* input_volume,
		orion_eigenvalue_feature_method method,
		bool apply_log,
		array_float* scales
	);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_COMPUTEEIGENVALUESGAUSSIANFILTER_H */
