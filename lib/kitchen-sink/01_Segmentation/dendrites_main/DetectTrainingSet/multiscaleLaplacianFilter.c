/* TODO
 *
 * Refactor: multiscaleLaplacianFilter
 */

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/multiscaleLaplacianFilter.h"

#include "util/util.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/Makefilter.h"
#include "ndarray/ndarray3_fft.h"


#define ORION_LAPLACIAN_HDAF_APPROX_DEGREE 60

/*
 * function that is used to normalize the response of the Laplacian filter
 */
float64 _orion_ConstantToNormalizeFilter( float64 sigma ) {
	return SQUARED( sigma );
}

void orion_multiscale_laplacian_output_free(orion_multiscale_laplacian_output* r) {
	if( r->laplacian )
		ndarray3_free( r->laplacian );

	if( r->max_response_at_scale_idx )
		ndarray3_free( r->max_response_at_scale_idx );

	free(r);
}

orion_multiscale_laplacian_output* orion_multiscale_laplacian_output_new() {
	orion_multiscale_laplacian_output* r;
	NEW(r, orion_multiscale_laplacian_output);
	r->laplacian = NULL;
	r->max_response_at_scale_idx = NULL;
	return r;
}

/*
 * function that allows to get the maximum reponse of the Laplacian
 *
 * laplacian_scales: scales to use for calculating the Laplacian. These are
 *                   separate from the scales in `orion_segmentation_param`.
 */
orion_multiscale_laplacian_output* orion_multiscaleLaplacianFilter(
		ndarray3* input_volume,
		array_float* laplacian_scales,
		orion_segmentation_param* p ) {
	orion_multiscale_laplacian_output* output =
		orion_multiscale_laplacian_output_new();

	int n = ORION_LAPLACIAN_HDAF_APPROX_DEGREE;

	/* Fourier transform the input image */
	ndarray3_complex* v_fft = ndarray3_fftn_r2c(input_volume);
	/*[>DEBUG<]ndarray3_complex_printf(v_fft, "v", "%8.3f", "%8.3f");*/
	/*[>REMOVE DEBUG<]{
		ndarray3* back =
			ndarray3_ifftn_c2r( v_fft );

		complex double ss = 0;
		float64 sss = 0;
		float64 inf_norm = -INFINITY;
		for( int i = 0; i < ndarray3_complex_elems(v_fft); i++ ) {
			sss += input_volume->p[i];
			ss += v_fft->p[i];

			float64 d = fabs(input_volume->p[i]
				- back->p[i]);
			if( d > inf_norm ) {
				[> find max <]
				inf_norm = d;
			}
		}
		printf("sss %f; sum = %g + %gi\n", sss, creal(ss), cimag(ss));
		complex_pixel_type zz000 = ndarray3_complex_get(v_fft, 0,0,0);
		printf("zz(0,0,0) %f + %fi\n",  creal(zz000), cimag(zz000));
		complex_pixel_type zz111 = ndarray3_complex_get(v_fft, 1,1,1);
		printf("zz(1,1,1) %f + %fi\n",  creal(zz111), cimag(zz111));
		printf("norm_∞: %f\n", inf_norm);


		ndarray3_free(back);

	}*/
	output->laplacian
		= ndarray3_complex_new(
			input_volume->sz[0],
			input_volume->sz[1],
			input_volume->sz[2] );
	output->max_response_at_scale_idx
		= ndarray3_new_with_size_from_ndarray3(input_volume);

	int nx = v_fft->sz[0], ny = v_fft->sz[1], nz = v_fft->sz[2];

	/* used to hold the Laplacian for a given scale */
	ndarray3_complex* cur_scale_laplacian =
		ndarray3_complex_new(
			input_volume->sz[0],
			input_volume->sz[1],
			input_volume->sz[2]
		);

	size_t lap_scale_len = array_length_float(laplacian_scales);
	bool recorded_maximum_scale = false;
	for( int lap_idx = 0; lap_idx < lap_scale_len; lap_idx++ ) {
		/* compute the Laplacian for each scale */
		float laplacian_scale_factor = array_get_float( laplacian_scales, lap_idx );

		float64 norm_const = _orion_ConstantToNormalizeFilter(laplacian_scale_factor);
		ndarray3* filt = orion_Makefilter( nx,ny,nz,
			n, laplacian_scale_factor, orion_Makefilter_FLAG_A);


		NDARRAY3_LOOP_OVER_START( filt, i,j,k) {
			/* normalise the generated Laplacian filter
			 *
			 *     filt /= norm_const;
			 */
			ndarray3_set(filt, i,j,k,
				ndarray3_get(filt, i,j,k)
				/ norm_const
			);

			/* Apply the filter to the input volume using pointwise
			 * multiplication in the Fourier domain.
			 *
			 *     cur_scale_laplacian = v_fft .* filt;
			 *
			 * NOTE: This is a complex multiplied by a scalar.
			 */
			ndarray3_complex_set(cur_scale_laplacian, i,j,k,
				  ndarray3_complex_get(v_fft, i,j,k)
				* ndarray3_get(filt,         i,j,k)
			);
		} NDARRAY3_LOOP_OVER_END;

		/* Now apply the inverse Fourier transform to bring the
		 * filtered volume back to the spatial domain */
		ndarray3* cur_scale_filt_vol =
			ndarray3_ifftn_c2r( cur_scale_laplacian );

		/* check for maximum response across all scales */
		if( !recorded_maximum_scale ) {
			NDARRAY3_LOOP_OVER_START( cur_scale_laplacian, i,j,k) {
				ndarray3_complex_set( output->laplacian, i,j,k,
					ndarray3_get(cur_scale_laplacian, i,j,k)
				    );
				ndarray3_set( output->max_response_at_scale_idx, i,j,k,
					lap_idx
				    );
			} NDARRAY3_LOOP_OVER_END;

			recorded_maximum_scale = true;
		} else {
			if( p->multiscale ) {
				/* Multiscale approach */
				NDARRAY3_LOOP_OVER_START( cur_scale_laplacian, i,j,k) {
					complex_pixel_type* cur = &ndarray3_get(cur_scale_laplacian, i,j,k);
					complex_pixel_type* lap = &ndarray3_get(output->laplacian, i,j,k);
					if(   cabsf(*cur) >= cabsf(*lap) ) {
						/* the current scale is recorded as the maximum at this point */
						*lap = *cur;
						ndarray3_set( output->scales, i,j,k,  lap_idx);
					}
				} NDARRAY3_LOOP_OVER_END;
			} else {
				/* ISBI 2014 */
				NDARRAY3_LOOP_OVER_START( cur_scale_laplacian, i,j,k) {
					complex_pixel_type* cur = &ndarray3_get(cur_scale_laplacian, i,j,k);
					complex_pixel_type* lap = &ndarray3_get(output->laplacian, i,j,k);
					if( *cur > *lap ) {
						*lap = *cur;
					}
				} NDARRAY3_LOOP_OVER_END;
			}
		}

		ndarray3_free(cur_scale_filt_vol);
		ndarray3_free(filt);
	}

	ndarray3_complex_free(cur_scale_laplacian);
	ndarray3_complex_free(v_fft);

	return output;
}
