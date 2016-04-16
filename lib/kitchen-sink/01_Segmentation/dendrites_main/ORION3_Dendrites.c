/* TODO
 *
 * Refactor: ORION3_Dendrites
 */


#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/readNegativeSamples.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/getFeatures.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/DiscriminantFunction/compute2D_DiscrimantFunction.h"

#include "kitchen-sink/01_Segmentation/dendrites_main/settingDefaultParameters.h"

#include "segmentation/orion_discriminant.h"
#include "numeric/random.h"

/*
 * Segmentation process which computes the distribution of the eigenvalues of
 * the Hessian matrix and assigns a cost function to eliminate background
 * voxels.
 *
 * Foreground voxels correspond to cost value larger than 0.5.
 */
void orion_ORION3_Dendrites(orion_segmentation_param* param, ndarray3* vol) {

	/* set the default parameters for the algorithm if none are set */
	orion_settingDefaultParameters( param );

	/* intialise PRNG */
	param->rng_state = kiss99_rng_state_new();
	kiss99_rng_init(param->rng_state);

	/*DEBUG*/orion_segmentation_param_dump( param );

	/*
	 * MAIN FUNCTION TO OBTAIN THE TRAINING SET OF BACKGROUND VOXELS
	 *
	 */
	/*
	 * STEP 1
	 * reading background samples using the Laplacian with the ISOTROPIC LOW
	 * PASS FILTER
	 */
	orion_readNegativeSamples(param, vol);

	WARN_UNIMPLEMENTED;
}
