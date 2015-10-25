#include "ndarray/ndarray3.h"

#include <math.h>

#include "util/string.h"

ndarray3* _ndarray3_init_sz(const size_t sz_x, const size_t sz_y, const size_t sz_z) {
	ndarray3* n;
	NEW(n, ndarray3);

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

ndarray3* ndarray3_wrap( float* p, const size_t sz_x, const size_t sz_y, const size_t sz_z ) {
	ndarray3* n = _ndarray3_init_sz(sz_x, sz_y, sz_z);

	n->p = p;
	n->wrap = true; /* we do not own this buffer, so we can not free it */

	return n;
}

ndarray3* ndarray3_buffer( float* p, const size_t sz_x, const size_t sz_y, const size_t sz_z ) {
	ndarray3* n = _ndarray3_init_sz(sz_x, sz_y, sz_z);

	n->p = p;
	n->wrap = false; /* we own this buffer and will free it ourselves */

	return n;
}

ndarray3* ndarray3_new(const size_t sz_x, const size_t sz_y, const size_t sz_z) {
	ndarray3* n = _ndarray3_init_sz(sz_x, sz_y, sz_z);

	NEW_COUNT( n->p, pixel_type, sz_x * sz_y * sz_z );
	n->wrap = false;

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

void ndarray3_printf( ndarray3* n, const char* variable_name, const char* format ) {
	for( int i = 0; i < n->sz[0]; i++ ) {
		printf("%s[%d][:][:] = {\n", variable_name, i);
		for( int j = 0; j < n->sz[1]; j++ ) {
			printf("\t");
			for( int k = 0; k < n->sz[2]; k++ ) {
				printf(format, ndarray3_get(n, i,j,k));
				printf(" ");
			}
			printf("\n");
		}
		printf("}\n");
	}
}

void ndarray3_printf_matlab( ndarray3* n, const char* variable_name, const char* format ) {
	for( int k = 0; k < n->sz[2]; k++ ) {
		printf("%s[:][:][%d] = {\n", variable_name, k);
		for( int i = 0; i < n->sz[0]; i++ ) {
			for( int j = 0; j < n->sz[1]; j++ ) {
			printf("\t");
				printf(format, ndarray3_get(n, i,j,k));
				printf(" ");
			}
			printf("\n");
		}
		printf("}\n");
	}
}

/* testing functions */
bool ndarray3_is_same_size( ndarray3* a, ndarray3* b ) {
	return    a->sz[0] == b->sz[0]
	       && a->sz[1] == b->sz[1]
	       && a->sz[2] == b->sz[2];
}

bool ndarray3_is_isotropic( const ndarray3* n, const pixel_type eps ) {
	bool is_isotropic = true;
	const size_t ndim = 3;
	size_t sz_half[ndim];
	size_t sz_even[ndim];
	for( int dim_idx = 0; dim_idx < ndim; dim_idx++ ) {
		sz_even[dim_idx] =      (n->sz[dim_idx] % 2  );
		sz_half[dim_idx] = floor(n->sz[dim_idx] / 2.0) + sz_even[dim_idx];
	}
	for( int i = 0; i < sz_half[0]; i++ ) {
		for( int j = 0; j < sz_half[1]; j++ ) {
			for( int k = 0; k < sz_half[2]; k++ ) {
				const pixel_type v = ndarray3_get(n, i, j, k );
				/*[>DEBUG<]printf("%d|%p at [%d,%d,%d] -> %f\n", is_isotropic, n, i, j, k, ndarray3_get(n, i, j, k ));*/

				/* indices reflected across the axes */
				ptrdiff_t fi = n->sz[0]-i-1;
				ptrdiff_t fj = n->sz[1]-j-1;
				ptrdiff_t fk = n->sz[2]-k-1;

				/* flip once */
				is_isotropic &= fabs( ndarray3_get(n, fi, j, k) - v ) < eps;
				is_isotropic &= fabs( ndarray3_get(n,  i,fj, k) - v ) < eps;
				is_isotropic &= fabs( ndarray3_get(n,  i, j,fk) - v ) < eps;

				/* flip twice */
				is_isotropic &= fabs( ndarray3_get(n, fi,fj, k) - v ) < eps;
				is_isotropic &= fabs( ndarray3_get(n, fi, j,fk) - v ) < eps;
				is_isotropic &= fabs( ndarray3_get(n,  i,fj,fk) - v ) < eps;

				/* flip thrice */
				is_isotropic &= fabs( ndarray3_get(n, fi,fj,fk) - v ) < eps;

				if( !is_isotropic ) {
					return is_isotropic;
				}
			}
		}
	}

	return is_isotropic;
}

/**
 * Sum over all the elements in the `ndarray3` `n`.
 */
float64 ndarray3_sum_over_all_float64( const ndarray3* n ) {
	float64 sum = 0; /* use larger type for precision */
	size_t elems = ndarray3_elems( n );
	/*[>DEBUG<]ndarray3_printf(n, "n", "%8.3e");*/
	for( size_t n_idx = 0; n_idx < elems; n_idx++ ) {
		sum += n->p[n_idx];
	}
	return sum;
}
