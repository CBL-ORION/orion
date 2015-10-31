#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <tap/basic.h>
#include <tap/float.h>

#include <kiss_fft.h>
#include <kiss_fftndr.h>

#include "util/util.h"
#include "ndarray/ndarray3.h"

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

	kiss_fft_cpx* freq_data;
	kiss_fft_scalar* inv_spatial_data;

	NEW_COUNT( freq_data, kiss_fft_cpx, n_nelems );
	NEW_COUNT( inv_spatial_data, kiss_fft_scalar, n_nelems );

	int dims[3];
	dims[0] = n->sz[0];
	dims[1] = n->sz[1];
	dims[2] = n->sz[2];
	float64 dim_prod = dims[0]*dims[1]*dims[2];
	kiss_fftndr_cfg fft =
		kiss_fftndr_alloc( dims, PIXEL_NDIMS, false , NULL, NULL);
	kiss_fftndr_cfg ifft =
		kiss_fftndr_alloc( dims, PIXEL_NDIMS, true , NULL, NULL);

	kiss_fftndr(fft, (kiss_fft_scalar*)(n->p), freq_data );
	kiss_fftndri(ifft, freq_data, inv_spatial_data );

	for( int i = 0; i < n_nelems; i++ ) {
		inv_spatial_data[i] /= dim_prod; /* scaling */
	}

	/*[>DEBUG<]{
		printf("Input:    \t\tOutput:\n");
		for( int i = 0; i < n_nelems; i++ ) {
			printf("%f\t\t%f\n",n->p[i], inv_spatial_data[i]);
		}
	}*/

	bool all_same = true;
#ifdef ORION_DEBUG
	float64 max_diff = -INFINITY;
	float64 square_error;
#endif
	for( int i = 0; i < n_nelems && all_same; i++ ) {
		/*[>DEBUG<]printf("[%d] : %g\n", i, fabs(array[i] - buf[i]));*/

		all_same = all_same && fabs(n->p[i] - inv_spatial_data[i]) < eps ;

#ifdef ORION_DEBUG
		float64 diff = n->p[i] - inv_spatial_data[i];
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
	free(freq_data);
	free(inv_spatial_data);

	free(fft);
	free(ifft);

	kiss_fft_cleanup();


	return EXIT_SUCCESS;
}
