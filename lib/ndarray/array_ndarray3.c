#include "ndarray3.h"

#define TYPE ndarray3
#define TYPED_NAME(x) x ## _ ## ndarray3
#include "container/array_impl.c"
#undef TYPE
#undef TYPED_NAME
