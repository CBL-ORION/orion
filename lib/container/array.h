#ifndef CONTAINER_ARRAY_H
#define CONTAINER_ARRAY_H 1

#define TYPE int
#define TYPED_NAME(x) x ## _ ## int
#include "array_impl.h"
#undef TYPE
#undef TYPED_NAME

#define TYPE float
#define TYPED_NAME(x) x ## _ ## float
#include "array_impl.h"
#undef TYPE
#undef TYPED_NAME

#define TYPE char*
#define TYPED_NAME(x) x ## _ ## str
#include "array_impl.h"
#undef TYPE
#undef TYPED_NAME

#endif /* CONTAINER_ARRAY_H */
