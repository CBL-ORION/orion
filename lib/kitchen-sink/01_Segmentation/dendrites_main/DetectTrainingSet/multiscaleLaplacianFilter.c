/* TODO
 *
 * Refactor: multiscaleLaplacianFilter
 */

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/multiscaleLaplacianFilter.h"

#include "util/util.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/Makefilter.h"


#define ORION_LAPLACIAN_HDAF_APPROX_DEGREE 60

/*
 * function that is used to normalize the response of the Laplacian filter
 */
float64 _orion_ConstantToNormalizeFilter( float64 sigma ) {
	return SQUARED( sigma );
}

ndarray3* ndarray3_fftn( ndarray3* n ) {
	WARN_UNIMPLEMENTED;
}

ndarray3* ndarray3_ifftn_symmetric( ndarray3* n ) {
	WARN_UNIMPLEMENTED;
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
	ndarray3* v_fft = ndarray3_fftn(input_volume);


	output->laplacian
		= ndarray3_new_with_size_from_ndarray3(input_volume);
	output->max_response_at_scale_idx
		= ndarray3_new_with_size_from_ndarray3(input_volume);

	int nx = v_fft->sz[0], ny = v_fft->sz[1], nz = v_fft->sz[2];

	/* used to hold the Laplacian for a given scale */
	ndarray3* cur_scale_laplacian =
		ndarray3_new_with_size_from_ndarray3(input_volume);

	size_t lap_scale_len = array_length_float(laplacian_scales);
	bool recorded_maximum_scale = false;
	for( int lap_idx = 0; lap_idx < lap_scale_len; lap_idx++ ) {
		float laplacian_scale_factor = array_get_float( laplacian_scales, lap_idx );

		float64 norm_const = _orion_ConstantToNormalizeFilter(laplacian_scale_factor);
		ndarray3* filt = orion_Makefilter( nx,ny,nz,
			n, laplacian_scale_factor, orion_Makefilter_FLAG_A);


		NDARRAY3_LOOP_OVER_START( filt, i,j,k) {
			/* normalise the generated Laplacian filter */
			ndarray3_set(filt, i,j,k,
				ndarray3_get(filt, i,j,k)
				/ norm_const
			);

			/* Apply the filter to the input volume using pointwise
			 * multiplication in the Fourier domain. */
			ndarray3_set(cur_scale_laplacian, i,j,k,
				  ndarray3_get(v_fft, i,j,k)
				* ndarray3_get(filt,         i,j,k)
			);
		} NDARRAY3_LOOP_OVER_END;

		/* Now apply the inverse Fourier transform to bring the
		 * filtered volume back to the spatial domain */
		ndarray3* cur_scale_filt_vol =
			ndarray3_ifftn_symmetric( cur_scale_laplacian );

		/* check for maximum response across all scales */
		if( !recorded_maximum_scale ) {
			NDARRAY3_LOOP_OVER_START( cur_scale_laplacian, i,j,k) {
				ndarray3_set( output->laplacian, i,j,k,
					ndarray3_get(cur_scale_laplacian, i,j,k)
				    );
				ndarray3_set( output->max_response_at_scale_idx, i,j,k,
					lap_idx
				    );
			} NDARRAY3_LOOP_OVER_END;

			recorded_maximum_scale = true;
		} else {
			if( p->multiscale ) {
				WARN_UNIMPLEMENTED;
			} else {
				WARN_UNIMPLEMENTED;
			}
		}
	}
	ndarray3_free(cur_scale_laplacian);

	return output;
}
