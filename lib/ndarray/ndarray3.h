#ifndef NDARRAY3_H
#define NDARRAY3_H 1

#include <stdlib.h>
#include <stdbool.h>

#include "config/datatype.h"
#include "util/util.h"

#include "ndarray/ndarray3_generic.h"

typedef struct {
	pixel_type* p;
	size_t sz[3]; /* PIXEL_NDIMS */
	bool wrap;

	bool has_spacing;
	pixel_type spacing[3]; /* PIXEL_NDIMS */
} ndarray3;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/***** CONSTRUCTORS *****/

/** TODO document
    ndarray3* ndarray3_new(const size_t sz_x, const size_t sz_y, const size_t sz_z)
 */

extern ndarray3* ndarray3_new(const size_t sz_x, const size_t sz_y, const size_t sz_z);

/* TODO document
 *
 * ndarray3* ndarray3_new_with_size_from_ndarray3(ndarray3* that)
 */
extern ndarray3* ndarray3_new_with_size_from_ndarray3(ndarray3* that);

/** TODO document
    ndarray3* ndarray3_wrap( pixel_type* p, const size_t sz_x, const size_t sz_y, const size_t sz_z )
 */
extern ndarray3* ndarray3_wrap( pixel_type* p, const size_t sz_x, const size_t sz_y, const size_t sz_z );

/** TODO document
 */
extern ndarray3* ndarray3_buffer( float* p, const size_t sz_x, const size_t sz_y, const size_t sz_z );

/***** DESTRUCTORS *****/

/** TODO document
    ndarray3_free( ndarray3* n )
 */

extern void ndarray3_free( ndarray3* n );

/** TODO document
 * Outputs information about the ndarray3 `n`.
 */
extern void ndarray3_dump( ndarray3* n );


/** TODO document
 *
 * Outputs the contents of the ndarray3 `n` with each element formatted using
 * the format specifier in `format`.
 */
extern void ndarray3_printf( ndarray3* n, const char* variable_name, const char* format );
extern void ndarray3_printf_matlab( ndarray3* n, const char* variable_name, const char* format );


/* testing functions */
extern bool ndarray3_is_same_size( ndarray3* a, ndarray3* b );
extern bool ndarray3_is_isotropic( const ndarray3* n, const pixel_type eps );

extern float64 ndarray3_sum_over_all_float64( const ndarray3* n );

#define ndarray3_set              ndarray3_generic_set
#define ndarray3_get              ndarray3_generic_get
#define ndarray3_elems            ndarray3_generic_elems
#define NDARRAY3_LOOP_OVER_START  NDARRAY3_GENERIC_LOOP_OVER_START
#define NDARRAY3_LOOP_OVER_END    NDARRAY3_GENERIC_LOOP_OVER_END


#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NDARRAY3_H */
