#ifndef CONTAINER_VECTOR_H
#define CONTAINER_VECTOR_H 1

#define TYPE int
#define TYPED_NAME(x) x ## _ ## int
#include "vector_impl.h"
#undef TYPE
#undef TYPED_NAME

#define TYPE float
#define TYPED_NAME(x) x ## _ ## float
#include "vector_impl.h"
#undef TYPE
#undef TYPED_NAME

#endif /* CONTAINER_VECTOR_H */
