#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/readNegativeSamples.h"

/* TODO
 *
 * Refactor: readNegativeSamples
 */
void orion_readNegativeSamples(
		orion_segmentation_param* param,
		ndarray3* input_volume ) {
	WARN_UNIMPLEMENTED;

	LOG_INFO("%s", "Detecting training set of background samples...");

	/*
	 * computing the scales of the filter in the Fourier domain. This is
	 * the main parameter to detect the boundary of the tubular structure.
	 */
	/*Lap = 0.5913./p.sigma;*/
	/*Lap = 0.66./p.sigma;*/
}
