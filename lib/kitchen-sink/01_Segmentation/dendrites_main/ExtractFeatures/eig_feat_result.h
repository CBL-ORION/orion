#ifndef ORION_EIG_FEAT_RESULT_H
#define ORION_EIG_FEAT_RESULT_H 1

#include "ndarray/array_ndarray3.h"

typedef struct {
	float scale;
	array_ndarray3* eig_feat;
} orion_eig_feat_result;

#endif /* ORION_EIG_FEAT_RESULT_H */
