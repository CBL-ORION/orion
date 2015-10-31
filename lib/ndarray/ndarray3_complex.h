#ifndef NDARRAY3_COMPLEX_H
#define NDARRAY3_COMPLEX_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>
#include <complex.h>

/* local headers */
#include "config/datatype.h"

/* structs, enums */
typedef struct {
	complex_pixel_type* p;
	size_t sz[3]; /* PIXEL_NDIMS */
	bool wrap;

	bool has_spacing;
	pixel_type spacing[3]; /* PIXEL_NDIMS */
} ndarray3_complex;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */



#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NDARRAY3_COMPLEX_H */
