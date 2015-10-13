#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include <math.h>
#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/Makefilter.h"

bool ndarray3_is_isotropic( const ndarray3* n, pixel_type eps ) {
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
				ptrdiff_t fi = n->sz[0]-i-1+!sz_even[0];
				ptrdiff_t fj = n->sz[1]-j-1+!sz_even[1];
				ptrdiff_t fk = n->sz[2]-k-1+!sz_even[2];

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

/*
% MATLAB
sz = 5;
mk = Makefilter(sz-1, sz, sz+1, 3, 5.0, 1 )

*/

int main(void) {
	const float64 eps = 1e-15;

	plan(3);

	int hdaf_approx_degree = 3;
	float scale_factor = 5.0;

	/*{
		[> even-sized filter <]
		const size_t SZ = 6;
		ndarray3* mk = orion_Makefilter( SZ, SZ, SZ, hdaf_approx_degree, scale_factor, orion_Makefilter_FLAG_A );
		ndarray3_printf_matlab( mk , "mk-even", "%8.4e");
		ndarray3_dump(mk);
		ok( ndarray3_is_isotropic( mk, eps ), "Makefilter() output is isotropic for an even-sized filter" );
		[>ndarray3_free(mk);<]
	}*/

	{
		/* odd-sized filter */
		const size_t SZ = 5;
		ndarray3* mk = orion_Makefilter( SZ, SZ, SZ, hdaf_approx_degree, scale_factor, orion_Makefilter_FLAG_A );
		ndarray3_printf_matlab( mk , "mk-odd", "%8.4e");
		ok( ndarray3_is_isotropic( mk, eps ), "Makefilter() output is isotropic for an odd-sized filter" );
		ndarray3_free(mk);
	}

	/*{
		[> asymmetric-sized filter <]
		const size_t SZ = 5;
		ndarray3* mk = orion_Makefilter( SZ-1, SZ, SZ+1, hdaf_approx_degree, scale_factor, orion_Makefilter_FLAG_A );
		ndarray3_printf_matlab( mk , "mk-asym", "%8.4e");
		ok( ndarray3_is_isotropic( mk, eps ), "Makefilter() output is isotropic for an asymmetric-sized filter" );
		[>ndarray3_free(mk);<]
	}*/

	return EXIT_SUCCESS;
}
