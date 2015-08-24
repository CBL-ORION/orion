#ifndef ARRAY_NDARRAY3_H
#define ARRAY_NDARRAY3_H 1

#include "ndarray3.h"

#define TYPE ndarray3
#define TYPED_NAME(x) x ## _ ## ndarray3
#include "container/array_impl.h"
#undef TYPE
#undef TYPED_NAME

#endif /* ARRAY_NDARRAY3_H */
