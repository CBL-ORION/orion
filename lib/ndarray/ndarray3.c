#include "ndarray/ndarray3.h"
#include "util/string.h"

ndarray3* ndarray3_wrap( float* p, const size_t sz_x, const size_t sz_y, const size_t sz_z ) {
	ndarray3* n;
	NEW(n, ndarray3);

	n->wrap = true;

	n->p = p;

	n->sz[0] = sz_x;
	n->sz[1] = sz_y;
	n->sz[2] = sz_z;

	return n;
}

ndarray3* ndarray3_new(const size_t sz_x, const size_t sz_y, const size_t sz_z) {
	ndarray3* n;
	NEW(n, ndarray3);

	NEW_COUNT( n->p, pixel_type, sz_x * sz_y * sz_y );
	n->wrap = false;

	n->sz[0] = sz_x;
	n->sz[1] = sz_y;
	n->sz[2] = sz_z;

	return n;
}


ndarray3* ndarray3_new_with_size_from_ndarray3(ndarray3* that) {
	return ndarray3_new( that->sz[0], that->sz[1], that->sz[2] );
}

void ndarray3_free( ndarray3* n ) {
	if( ! n->wrap ) free( n->p );
	free( n );
}

void ndarray3_dump( ndarray3* n ) {
	fprintf(stderr, "ndarray3: %p\n"
			"\tsize: [ "
				SIZE_T_FORMAT_SPEC " "
				SIZE_T_FORMAT_SPEC " "
				SIZE_T_FORMAT_SPEC " "
				"]\n"
			"\tdata: %p\n"
			"\twrap: %s\n"
				,
				n,
				n->sz[0],
				n->sz[1],
				n->sz[2],
				n->p,
				btoa(n->wrap) );
}

void ndarray3_print( ndarray3* n ) {
	for( int i = 0; i < n->sz[0]; i++ ) {
		printf("x[%d][:][:] = {\n", i);
		for( int j = 0; j < n->sz[1]; j++ ) {
			printf("\t");
			for( int k = 0; k < n->sz[2]; k++ ) {
				printf("%-9.3e ", ndarray3_get(n, i,j,k));
			}
			printf("\n");
		}
		printf("}\n");
	}
}
