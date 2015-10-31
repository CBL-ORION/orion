#ifndef NDARRAY3_COMPLEX_H
#define NDARRAY3_COMPLEX_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>
#include <complex.h>

/* local headers */
#include "config/datatype.h"

#include "ndarray/ndarray3_generic.h"

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
extern ndarray3_complex* _ndarray3_complex_init_sz(const size_t sz_x, const size_t sz_y, const size_t sz_z);
extern ndarray3_complex* ndarray3_complex_new(const size_t sz_x, const size_t sz_y, const size_t sz_z);
extern void ndarray3_complex_free( ndarray3_complex* n );


#define ndarray3_complex_set              ndarray3_generic_set
#define ndarray3_complex_get              ndarray3_generic_get
#define ndarray3_complex_elems            ndarray3_generic_elems
#define NDARRAY3_COMPLEX_LOOP_OVER_START  NDARRAY3_GENERIC_LOOP_OVER_START
#define NDARRAY3_COMPLEX_LOOP_OVER_END    NDARRAY3_GENERIC_LOOP_OVER_END

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NDARRAY3_COMPLEX_H */
