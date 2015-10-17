#ifndef ORION_EIG_FEAT_RESULT_H
#define ORION_EIG_FEAT_RESULT_H 1

/* local headers */
#include "ndarray/array_ndarray3.h"

/* structs, enums */
typedef struct {
	float scale;
	array_ndarray3* eig_feat;
} orion_eig_feat_result;

/* functions */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern orion_eig_feat_result* orion_eig_feat_result_new();
void orion_eig_feat_result_free(orion_eig_feat_result* e);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_EIG_FEAT_RESULT_H */
