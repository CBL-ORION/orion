#ifndef CONTAINER_ARRAY_H
#define CONTAINER_ARRAY_H 1

#define TYPE int
#define TYPED_NAME(x) x##_int
#include "array_impl.h"
#undef TYPE
#undef TYPED_NAME

#define TYPE float
#define TYPED_NAME(x) x##_float
#include "array_impl.h"
#undef TYPE
#undef TYPED_NAME

#endif /* CONTAINER_ARRAY_H */
