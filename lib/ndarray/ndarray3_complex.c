#include "ndarray/ndarray3_complex.h"

ndarray3_complex* _ndarray3_complex_init_sz(const size_t sz_x, const size_t sz_y, const size_t sz_z) {
	ndarray3_complex* n;
	NEW(n, ndarray3_complex);

	n->sz[0] = sz_x;
	n->sz[1] = sz_y;
	n->sz[2] = sz_z;

	n->has_spacing = 0;
	/* default spacing */
	n->spacing[0] = 1;
	n->spacing[1] = 1;
	n->spacing[2] = 1;

	return n;
}

ndarray3_complex* ndarray3_complex_new(const size_t sz_x, const size_t sz_y, const size_t sz_z) {
	ndarray3_complex* n = _ndarray3_complex_init_sz(sz_x, sz_y, sz_z);

	NEW_COUNT( n->p, complex_pixel_type, sz_x * sz_y * sz_z );
	n->wrap = false;

	return n;
}

void ndarray3_complex_free( ndarray3_complex* n ) {
	if( ! n->wrap ) free( n->p );
	free( n );
}
