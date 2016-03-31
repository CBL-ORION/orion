#include "ndarray/ndarray3_fft.h"

#include "simple-log/simplelog.h"

#include <kiss_fft.h>
#include <kiss_fftndr.h>

ndarray3_complex* ndarray3_fftn_r2c( ndarray3* n ) {
	int* dims;
	NEW_COUNT( dims, int, PIXEL_NDIMS );
	dims[0] = n->sz[0];
	dims[1] = n->sz[1];
	dims[2] = n->sz[2];
	ndarray3_dump(n);
	if( !n->has_zero_padding_on_last_dim && dims[2] % 2 != 0 ) {
		LOG_DEBUG("%s", "Resizing ndarray3 for FFT");
		RESIZE_COUNT( n->p, pixel_type, ndarray3_elems(n) + (  n->sz[0] * n->sz[1] ) );
		LOG_DEBUG("%s", "Zero-padding along the last dimension");
		n->sz[2]++; /* temprorarily increase size */
		for( int i = 0; i < n->sz[0]; i++ ) {
			for( int j = 0; j < n->sz[1]; j++ ) {
				/* zero pad last dimension */
				ndarray3_set(n, i, j, n->sz[2]-1, 0 );
			}
		}
		n->sz[2]--;
		n->has_zero_padding_on_last_dim = true;
	}
	if( n->has_zero_padding_on_last_dim ) {
		dims[2]++;
	}
	LOG_DEBUG("Dims: [ %d %d %d ]", dims[0], dims[1], dims[2]);

	ndarray3_complex* freq_data =
		ndarray3_complex_new(dims[0], dims[1], dims[2]);


	kiss_fftndr_cfg fft =
		kiss_fftndr_alloc( dims, PIXEL_NDIMS, false , NULL, NULL);

	kiss_fftndr(fft, (kiss_fft_scalar*)(n->p), freq_data->p );


	if( n->has_zero_padding_on_last_dim ) {
		LOG_DEBUG("%s", "Truncating the frequency data");
		RESIZE_COUNT( freq_data->p, complex_pixel_type, ndarray3_elems(n) );
		freq_data->sz[2]--;
	}

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

	kiss_fftndri(ifft, n->p, spatial_data->p );

	size_t nelems = ndarray3_complex_elems( n );
	for( int i = 0; i < nelems; i++ ) {
		spatial_data->p[i] /= nelems; /* scaling */
	}

	free(dims);
	free(ifft);

	return spatial_data;
}
