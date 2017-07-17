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
	orion_multiscale_laplacian_output*
		lap_output = orion_readNegativeSamples(param, vol);

	/*
	 * STEP 2
	 *
	 * Compute the feature vector
	 */
	orion_features* features = orion_getFeatures( param, vol, lap_output );

	/* STEP 3
	 *
	 * Compute the discriminant functions and their response
	 */
	pixel_type min_scale, max_scale;
	ndarray3_minmax(lap_output->max_response_at_scale_idx,
			&min_scale, &max_scale );
	/* Compute the discriminant function for each scale. */
	orion_discriminant_function* discrim;
	/* used to store the indices of the training instances */
	array_int* scale_instances = array_new_int(10);
	for( int scale_idx = min_scale; scale_idx <= max_scale; scale_idx++ ) {
		/* Training instances for current scale:
		 * Find all background features for this scale.
		 */
		array_reset_int(scale_instances); /* start the count over again */
		for( size_t f_idx = 0; f_idx < features->number_of_instances; f_idx++ ) {
			bool feat_is_background = (bool)(lap_output->is_background->p[f_idx]);
			size_t feat_scale = (size_t)(lap_output->max_response_at_scale_idx->p[f_idx]);

			if( feat_is_background && feat_scale == scale_idx ) {
				array_add_int( scale_instances, f_idx );
			}
		}
		LOG_DEBUG("There are %d training samples for the scale %f [index: %d]",
				array_length_int(scale_instances),
				array_get_float( param->scales, scale_idx ),
				scale_idx );

		orion_compute2D_DiscrimantFunction(param, features, scale_instances, discrim);
	}
	array_free_int(scale_instances);

	WARN_UNIMPLEMENTED;

	orion_multiscale_laplacian_output_free( lap_output );
	orion_features_free(features);
	kiss99_rng_state_free( param->rng_state );
}
