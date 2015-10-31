#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <tap/basic.h>
#include <tap/float.h>

#include "util/util.h"
#include "ndarray/ndarray3_fft.h"

int main(void) {
	plan(1);

	/* an epsilon of 1e-7 is expected when dealing with
	 * single-precision FFT */
	const float64 eps = 1e-7;

	ndarray3* n = ndarray3_new( 4, 4, 4 );
	const size_t n_nelems = ndarray3_elems( n );
	for( int idx = 0; idx < n_nelems; idx++ ) {
		n->p[idx] = idx;
	}

	ndarray3_complex* freq_data = ndarray3_fftn_r2c( n );
	ndarray3* inv_spatial_data = ndarray3_ifftn_c2r( freq_data );

	/*[>DEBUG<]{
		printf("Input:    \t\tOutput:\n");
		for( int i = 0; i < n_nelems; i++ ) {
			printf("%f\t\t%f\n",n->p[i], inv_spatial_data->p[i]);
		}
	}*/

	bool all_same = true;
#ifdef ORION_DEBUG
	float64 max_diff = -INFINITY;
	float64 square_error;
#endif
	for( int i = 0; i < n_nelems && all_same; i++ ) {
		/*[>DEBUG<]printf("[%d] : %g\n", i, fabs(array[i] - buf[i]));*/

		all_same = all_same && fabs(n->p[i] - inv_spatial_data->p[i]) < eps ;

#ifdef ORION_DEBUG
		float64 diff = n->p[i] - inv_spatial_data->p[i];
		square_error += SQUARED(diff);
		if( max_diff < fabs(diff) ) {
			max_diff = fabs(diff);
		}
#endif
	}

#ifdef ORION_DEBUG
	diag( "RMS: %g", sqrt(square_error/n_nelems) );
	diag( "error [infinity norm]: %g", max_diff );
#endif
	ok( all_same, "ifft(fft(x)) == x");

	ndarray3_free(n);
	ndarray3_complex_free(freq_data);
	ndarray3_free(inv_spatial_data);

	kiss_fft_cleanup();

	return EXIT_SUCCESS;
}
