#define TYPE int
#define TYPED_NAME(x) x ## _ ## int
#include "array_impl.c"
#undef TYPE
#undef TYPED_NAME

#define TYPE float
#define TYPED_NAME(x) x ## _ ## float
#include "array_impl.c"
#undef TYPE
#undef TYPED_NAME
