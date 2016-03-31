#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/readNegativeSamples.h"

/* TODO
 *
 * Refactor: readNegativeSamples
 */
orion_multiscale_laplacian_output*
orion_readNegativeSamples(
		orion_segmentation_param* param,
		ndarray3* vol ) {
	LOG_INFO("%s", "Detecting training set of background samples...");

	/*
	 * computing the scales of the filter in the Fourier domain. This is
	 * the main parameter to detect the boundary of the tubular structure.
	 */
	/*Lap = 0.5913./p.sigma;*/
	/*Lap = 0.66./p.sigma;*/
	/*%n=60;Lap = sqrt(2.0*n+1)./(sqrt(2)*(3.6853*p.sigma - 2.1676)*pi);*/
	size_t n_scales = array_length_float( param->scales );
	array_float* Lap =  array_new_float( n_scales );
	for( size_t Lap_idx = 0; Lap_idx < n_scales; Lap_idx++ ) {
		array_set_float( Lap, Lap_idx,
			0.66 / array_get_float( param->scales, Lap_idx ) );
	}

	orion_multiscale_laplacian_output* lap_out = orion_multiscaleLaplacianFilter( vol, Lap, param );


	/* Only the positive values are background voxels.
	 *
	 * We set the `laplacian` member to 1.0 or 0.0 depending on if it is in
	 * the background.
	 */
	NDARRAY3_LOOP_OVER_START( lap_out->laplacian, i,j,k) {
		ndarray3_set( lap_out->laplacian, i,j,k,
			ndarray3_get( lap_out->laplacian, i,j,k) > 0 );
	} NDARRAY3_LOOP_OVER_END;

	return lap_out;
}
