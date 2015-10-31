#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <tap/basic.h>
#include <tap/float.h>

#include <kiss_fft.h>
#include <kiss_fftr.h>

#include "util/util.h"

kiss_fft_cpx* copycpx(float *mat, int nframe) {
	int i;
	kiss_fft_cpx *mat2;
	mat2=(kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx)*nframe);
	kiss_fft_scalar zero;
	memset(&zero,0,sizeof(zero) );
	for( i=0; i<nframe ; i++ ) {
		mat2[i].r = mat[i];
		mat2[i].i = zero;
	}
	return mat2;
}

int main(void) {
	plan(1);

	/* an epsilon of 1e-7 is expected when dealing with
	 * single-precision FFT */
	const float64 eps = 1e-7;

	int i, size = 12;
	int isinverse = 1;
	float buf[size];
	float array[] =
		{ 0.1, 0.6, 0.1, 0.4,
		  0.5, 0  , 0.8, 0.7,
		  0.8, 0.6, 0.1, 0 };

	kiss_fft_cpx out_cpx[size],out[size],*cpx_buf;

	kiss_fftr_cfg fft =  kiss_fftr_alloc(size*2, 0        ,NULL,NULL);
	kiss_fftr_cfg ifft = kiss_fftr_alloc(size*2, isinverse,NULL,NULL);

	cpx_buf = copycpx(array,size);

	kiss_fftr(fft,(kiss_fft_scalar*)cpx_buf, out_cpx );
	kiss_fftri(ifft,out_cpx,(kiss_fft_scalar*)out );

	for( i=0; i<size; i++ ) {
		buf[i] = (out[i].r)/(size*2); /* scaling */
	}

	/*[>DEBUG<]{
		printf("Input:    \t\tOutput:\n");
		for( i=0; i<size; i++ ) {
			printf("%f\t\t%f\n",array[i],buf[i]);
		}
	}*/

	bool all_same = true;
#ifdef ORION_DEBUG
	float64 max_diff = -INFINITY;
	float64 square_error;
#endif
	for( int i = 0; i < size && all_same; i++ ) {
		/*[>DEBUG<]printf("[%d] : %g\n", i, fabs(array[i] - buf[i]));*/

		all_same = all_same && fabs(array[i] - buf[i]) < eps ;

#ifdef ORION_DEBUG
		float64 diff = array[i] - buf[i];
		square_error += SQUARED(diff);
		if( max_diff < fabs(diff) ) {
			max_diff = fabs(diff);
		}
#endif
	}

#ifdef ORION_DEBUG
	diag( "RMS: %g", sqrt(square_error/size) );
	diag( "error [infinity norm]: %g", max_diff );
#endif
	ok( all_same, "ifft(fft(x)) == x");

	kiss_fft_cleanup();
	kiss_fft_free( cpx_buf );
	free(fft);
	free(ifft);



	return EXIT_SUCCESS;
}
