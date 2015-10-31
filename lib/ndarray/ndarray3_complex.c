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


void ndarray3_complex_printf(ndarray3_complex* n,
		const char* variable_name,
		const char* real_format,
		char* imag_format) {
	for( int i = 0; i < n->sz[0]; i++ ) {
		printf("%s[%d][:][:] = {\n", variable_name, i);
		for( int j = 0; j < n->sz[1]; j++ ) {
			printf("\t");
			for( int k = 0; k < n->sz[2]; k++ ) {
				complex_pixel_type z =
					ndarray3_complex_get( n, i,j,k);
				printf(real_format, creal(z) );
				printf(" %c ", cimag(z) >= 0 ? '+' : '-');
				printf(imag_format, cimag(z) );
				printf(" ");
			}
			printf("\n");
		}
		printf("}\n");
	}
}
