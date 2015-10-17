#ifndef NDARRAY3_H
#define NDARRAY3_H 1

#include <stdlib.h>
#include <stdbool.h>

#include "config/datatype.h"
#include "util/util.h"
#include "util/likely.h"

typedef struct {
	pixel_type* p;
	size_t sz[3];
	bool wrap;
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

extern pixel_type ndarray3_sum_over_all( const ndarray3* n );

/** TODO document
    _INDEX3D( int i, int j, int k, int size_x, int size_y,  int size_z )
 */
#define _INDEX3D(_i, _j, _k, _sz_x, _sz_y, _sz_z)   ((_k*_sz_y+_j) * _sz_x + _i)

#define _ndarray3_index(_n, _n_i, _n_j, _n_k) \
( \
	(_n)->p + _INDEX3D( (_n_i), (_n_j), (_n_k), (_n)->sz[0], (_n)->sz[1], (_n)->sz[2] ) \
)

#define _ndarray3_assert_bounds(_n, _n_i, _n_j, _n_k) ( \
		   _n_i >=0 && _n_i < _n->sz[0] \
		&& _n_j >=0 && _n_j < _n->sz[1] \
		&& _n_k >=0 && _n_k < _n->sz[2] \
		)



/** TODO document
 *  ndarray3_set( ndarray3* n, size_t i, size_t j, size_t k, pixel_type value )
 */
#define _real_ndarray3_set(_n, _n_i, _n_j, _n_k, val) \
	do { \
		*_ndarray3_index( (_n), (_n_i), (_n_j), (_n_k) ) = (val); \
	} while(0)
#ifdef NDARRAY3_ASSERT_BOUNDS_ACCESS
  #define ndarray3_set(_n, _n_i, _n_j, _n_k, val) \
	do { \
		if( likely(_ndarray3_assert_bounds(_n, _n_i, _n_j, _n_k)) ) { \
			_real_ndarray3_set(_n, _n_i, _n_j, _n_k, val); \
		} else { \
			die("ndarray3 (%p) access [%d,%d,%d]", _n, _n_i,_n_j,_n_k); \
		} \
	} while(0)
#else
  #define ndarray3_set(_n, _n_i, _n_j, _n_k, val) \
	_real_ndarray3_set(_n, _n_i, _n_j, _n_k, val)
#endif /* NDARRAY3_ASSERT_BOUNDS_ACCESS */

/** TODO document
 *  ndarray3_elems( ndarray3* n )
 *
 *  Number of elements in `n`. This is the product of the dimensions of `n`.
 */
#define ndarray3_elems(_n) ( (_n)->sz[0] * (_n)->sz[1] * (_n)->sz[2] )

/** TODO document
 *  ndarray3_get( ndarray3* n, size_t i, size_t j, size_t k              )
 */
#define _real_ndarray3_get(_n, _n_i, _n_j, _n_k     )    ( *_ndarray3_index( (_n), (_n_i), (_n_j), (_n_k) )       )

#ifdef NDARRAY3_ASSERT_BOUNDS_ACCESS
  #define ndarray3_get(_n, _n_i, _n_j, _n_k           )    \
        ( \
          ( likely(_ndarray3_assert_bounds(_n, _n_i, _n_j, _n_k )) ) \
        ? ( _real_ndarray3_get(_n, _n_i, _n_j, _n_k     ) ) \
        : (  die("ndarray3 (%p) access [%d,%d,%d]", _n, _n_i, _n_j, _n_k ),0 ) \
        )
#else
  #define ndarray3_get(_n, _n_i, _n_j, _n_k           )   \
        ( _real_ndarray3_get(_n, _n_i, _n_j, _n_k     ) )
#endif /* NDARRAY3_ASSERT_BOUNDS_ACCESS */


/** TODO document
 *  NDARRAY3_LOOP_OVER_START( ndarray3* n, size_t i, size_t j, size_t k ) {
 *      / * code body * /
 *  } NDARRAY3_LOOP_OVER_END;
 *
 *      NDARRAY3_LOOP_OVER_START( n, i, j, k) {
 *          ndarray3_set(n, i, j, k, 0);
 *      } NDARRAY3_LOOP_OVER_END;
 */
#define NDARRAY3_LOOP_OVER_START( _ndarray3_var, _i0, _i1, _i2 ) \
	do { \
	/* start of NDARRAY3_LOOP_OVER_* */ \
		for( size_t _i0 = 0; _i0 < _ndarray3_var->sz[0]; _i0++ ) { \
		for( size_t _i1 = 0; _i1 < _ndarray3_var->sz[1]; _i1++ ) { \
		for( size_t _i2 = 0; _i2 < _ndarray3_var->sz[2]; _i2++ ) { \
			/* NDARRAY3_LOOP_OVER_* body goes here */

#define NDARRAY3_LOOP_OVER_END \
			/* NDARRAY3_LOOP_OVER_* body ends here */ \
		} \
		} \
		} \
	/* end of NDARRAY3_LOOP_OVER_* */ \
	} while(0)


#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NDARRAY3_H */
