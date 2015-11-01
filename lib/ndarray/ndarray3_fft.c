#include "ndarray/ndarray3_fft.h"

#include <kiss_fft.h>
#include <kiss_fftndr.h>

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

	kiss_fftndr(fft, (kiss_fft_scalar*)(n->p), freq_data->p );

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
