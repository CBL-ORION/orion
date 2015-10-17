#ifndef ARRAY_ORION_EIG_FEAT_RESULT_H
#define ARRAY_ORION_EIG_FEAT_RESULT_H 1

#include "eig_feat_result.h"

#define TYPE orion_eig_feat_result*
#define TYPED_NAME(x) x ## _ ## orion_eig_feat_result
#include "container/array_impl.h"
#undef TYPE
#undef TYPED_NAME

#endif /* ARRAY_ORION_EIG_FEAT_RESULT_H */
