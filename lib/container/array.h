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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* TODO make more generic */
extern void array_dump_float(array_float* array);
extern void array_dump_str(array_str* array);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* CONTAINER_ARRAY_H */
