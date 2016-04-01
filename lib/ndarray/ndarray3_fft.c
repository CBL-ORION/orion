#include "ndarray/ndarray3_fft.h"

#include <kiss_fft.h>
#include <kiss_fftndr.h>
#include <kiss_fftnd.h>

ndarray3_complex* ndarray3_fftn_r2c( ndarray3* n ) {
	ndarray3_complex* freq_data =
		ndarray3_complex_new(n->sz[0], n->sz[1], n->sz[2]);

	int* dims;
	NEW_COUNT( dims, int, PIXEL_NDIMS );
	dims[0] = n->sz[0];
	dims[1] = n->sz[1];
	dims[2] = n->sz[2];
	kiss_fftndr_cfg fft =
		kiss_fftndr_alloc( dims, PIXEL_NDIMS, false , NULL, NULL);

	kiss_fftndr(fft, (kiss_fft_scalar*)(n->p), (kiss_fft_cpx *)(freq_data->p) );

	free(dims);
	free(fft);

	return freq_data;
}

ndarray3* ndarray3_ifftn_c2r( ndarray3_complex* n ) {
	ndarray3* spatial_data =
		ndarray3_new(n->sz[0], n->sz[1], n->sz[2]);

	int* dims;
	NEW_COUNT( dims, int, PIXEL_NDIMS );
	dims[0] = n->sz[0];
	dims[1] = n->sz[1];
	dims[2] = n->sz[2];

	kiss_fftndr_cfg ifft =
		kiss_fftndr_alloc( dims, PIXEL_NDIMS, true , NULL, NULL);

	kiss_fftndri(ifft, (kiss_fft_cpx *)(n->p), spatial_data->p );

	size_t nelems = ndarray3_complex_elems( n );
	for( int i = 0; i < nelems; i++ ) {
		spatial_data->p[i] /= nelems; /* scaling */
	}

	free(dims);
	free(ifft);

	return spatial_data;
}

ndarray3_complex* ndarray3_fftn_real( ndarray3* n ) {
	ndarray3_complex* space_data =
		ndarray3_complex_new(n->sz[0], n->sz[1], n->sz[2]);
	NDARRAY3_LOOP_OVER_START( n, i,j,k ) {
		ndarray3_complex_set( space_data, i,j,k, ndarray3_get(n, i,j,k) );
	} NDARRAY3_LOOP_OVER_END;

	ndarray3_complex* freq_data =
		ndarray3_complex_new(n->sz[0], n->sz[1], n->sz[2]);

	int* dims;
	NEW_COUNT( dims, int, PIXEL_NDIMS );
	dims[0] = n->sz[0];
	dims[1] = n->sz[1];
	dims[2] = n->sz[2];
	kiss_fftnd_cfg fft =
		kiss_fftnd_alloc( dims, PIXEL_NDIMS, false , NULL, NULL);
	/*                                           ^
	 *                                           |
	 *                                           +---- forward FFT
	 */

	kiss_fftnd(fft, (kiss_fft_cpx *)(space_data->p), (kiss_fft_cpx *)(freq_data->p) );

	ndarray3_complex_free(space_data);
	free(dims);
	free(fft);

	return freq_data;
}

ndarray3* ndarray3_ifftn_real( ndarray3_complex* n ) {
	ndarray3_complex* spatial_data_complex =
		ndarray3_complex_new(n->sz[0], n->sz[1], n->sz[2]);

	ndarray3* spatial_data =
		ndarray3_new(n->sz[0], n->sz[1], n->sz[2]);

	int* dims;
	NEW_COUNT( dims, int, PIXEL_NDIMS );
	dims[0] = n->sz[0];
	dims[1] = n->sz[1];
	dims[2] = n->sz[2];

	kiss_fftnd_cfg ifft =
		kiss_fftnd_alloc( dims, PIXEL_NDIMS, true , NULL, NULL);
	/*                                           ^
	 *                                           |
	 *                                           +---- inverse FFT
	 */

	kiss_fftnd(ifft, (kiss_fft_cpx *)(n->p), (kiss_fft_cpx *)(spatial_data_complex->p) );

	size_t nelems = ndarray3_complex_elems( n );
	for( int i = 0; i < nelems; i++ ) {
		spatial_data->p[i] /= nelems; /* scaling */
	}

	/* keep real part of `spatial_data_complex` */
	NDARRAY3_LOOP_OVER_START( spatial_data_complex, i,j,k ) {
		ndarray3_set( spatial_data, i,j,k,
				crealf( ndarray3_complex_get( spatial_data_complex, i,j,k) )
				);
	} NDARRAY3_LOOP_OVER_END;

	ndarray3_complex_free(spatial_data_complex);
	free(dims);
	free(ifft);

	return spatial_data;
}


