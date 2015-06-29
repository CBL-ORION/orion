#ifndef NDARRAY3_H
#define NDARRAY3_H 1

#include <stdlib.h>

typedef struct {
	float* p;
	size_t sz[3];
	int wrap;
} ndarray3;


/***** CONSTRUCTORS *****/

/** TODO
    ndarray3* ndarray3_create(const size_t sz_x, const size_t sz_y, const size_t sz_z)
 */

ndarray3* ndarray3_create(const size_t sz_x, const size_t sz_y, const size_t sz_z);

/** TODO
    ndarray3* ndarray3_wrap( const float* p, const size_t sz_x, const size_t sz_y, const size_t sz_z )
 */
ndarray3* ndarray3_wrap( const float* p, const size_t sz_x, const size_t sz_y, const size_t sz_z );

/***** DESTRUCTORS *****/

/** TODO
    ndarray3_destroy( ndarray3* n )
 */

void ndarray3_destroy( ndarray3* n );

/** TODO
    _INDEX3D( int i, int j, int k, int size_x, int size_y,  int size_z )
 */
#define _INDEX3D(_i, _j, _k, _sz_x, _sz_y, _sz_z)   ((_z*_sz_y+_j) * _sz_x + _i)

#define _ndarray3_index(_n, _n_i, _n_j, _n_k) \
( \
	(_n)->p + _INDEX3D( (_n_i), (_n_j), (_n_k), (_n)->sz[0], (_n)->sz[1], (_n)->sz[2] ) \
)


/** TODO
    ndarray3_set( ndarray3* n, size_t i, size_t j, size_t k, float value )
 */
#define ndarray3_set(_n, _n_i, _n_j, _n_k, val) do { *_ndarray3_index( (_n), (_n_i), (_n_j), (_n_k) ) = val }

/** TODO
    ndarray3_get( ndarray3* n, size_t i, size_t j, size_t k              )
 */
#define ndarray3_get(_n, _n_i, _n_j, _n_k     )    ( *_ndarray3_index( (_n), (_n_i), (_n_j), (_n_k) )       )

#endif
