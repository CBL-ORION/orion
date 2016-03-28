/* TODO
 *
 * Refactor: multiscaleLaplacianFilter
 */

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/multiscaleLaplacianFilter.h"

#include "util/util.h"
#include "simple-log/simplelog.h"
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

	output->laplacian
		= ndarray3_new_with_size_from_ndarray3(input_volume);
	output->max_response_at_scale_idx
		= ndarray3_new_with_size_from_ndarray3(input_volume);

	int nx = v_fft->sz[0], ny = v_fft->sz[1], nz = v_fft->sz[2];

	/* used to hold the Laplacian response in the Fourier domain for a
	 * given scale
	 */
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
		LOG_INFO("Computing Laplacian using scale: %f", laplacian_scale_factor);

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
				  ndarray3_complex_get(v_fft,     i,j,k)
				* ndarray3_get(filt,              i,j,k)
			);
		} NDARRAY3_LOOP_OVER_END;

		/* Now apply the inverse Fourier transform to bring the
		 * filtered volume back to the spatial domain.
		 *
		 * Again, note that the response is real because the input data
		 * is real and we treat the data in `cur_scale_laplacian` after
		 * applying the filter as conjugate symmetric.
		 * */
		ndarray3* cur_scale_filt_vol =
			ndarray3_ifftn_c2r( cur_scale_laplacian );

		/* check for maximum response across all scales */
		if( !recorded_maximum_scale ) {
			NDARRAY3_LOOP_OVER_START( cur_scale_filt_vol, i,j,k) {
				ndarray3_set( output->laplacian, i,j,k,
					ndarray3_get(cur_scale_filt_vol, i,j,k)
				    );
				ndarray3_set( output->max_response_at_scale_idx, i,j,k,
					lap_idx
				    );
			} NDARRAY3_LOOP_OVER_END;

			recorded_maximum_scale = true;
		} else {
			if( p->multiscale ) {
				/* Multiscale approach */
				NDARRAY3_LOOP_OVER_START( cur_scale_filt_vol, i,j,k) {
					pixel_type cur = ndarray3_get(cur_scale_filt_vol, i,j,k);
					pixel_type lap = ndarray3_get(output->laplacian,  i,j,k);
					if(   fabs(cur) >= fabs(lap) ) {
						/* the current scale is recorded as the maximum at this point */
						ndarray3_set(output->laplacian, i,j,k, lap);
						ndarray3_set(output->max_response_at_scale_idx, i,j,k,  lap_idx);
					}
				} NDARRAY3_LOOP_OVER_END;
			} else {
				/* ISBI 2014 */
				/* Check if the values themselves are larger
				 * than the current maximum
				 */
				NDARRAY3_LOOP_OVER_START( cur_scale_filt_vol, i,j,k) {
					pixel_type cur = ndarray3_get(cur_scale_filt_vol, i,j,k);
					pixel_type lap = ndarray3_get(output->laplacian, i,j,k);
					if( cur > lap ) {
						ndarray3_set(output->laplacian, i,j,k, cur);
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
