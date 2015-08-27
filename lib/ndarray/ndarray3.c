#include "ndarray/ndarray3.h"

ndarray3* ndarray3_wrap( const float* p, const size_t sz_x, const size_t sz_y, const size_t sz_z ) {
	ndarray3* n;
	NEW(n, ndarray3);

	n->wrap = 1;

	n->sz[0] = sz_x;
	n->sz[1] = sz_y;
	n->sz[2] = sz_z;

	return n;
}

ndarray3* ndarray3_new(const size_t sz_x, const size_t sz_y, const size_t sz_z) {
	ndarray3* n;
	NEW(n, ndarray3);

	NEW_COUNT( n->p, pixel_type, sz_x * sz_y * sz_y );
	n->wrap = 0;

	n->sz[0] = sz_x;
	n->sz[1] = sz_y;
	n->sz[2] = sz_z;

	return n;
}

void ndarray3_free( ndarray3* n ) {
	if( ! n->wrap ) free( n->p );
	free( n );
}
