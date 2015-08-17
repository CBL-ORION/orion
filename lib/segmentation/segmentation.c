#include "param/param.h"

/* TODO:
 *
 * Refactor: ORION3_Dendrites
 *
 */

/* TODO
 * Segmentation algorithm
 *
 * One-Class Classification for Segmentation of Neuron (OCCEN)
 *
 * Input: A 3D image stack I and a radius r
 *
 * Output: Label 0 for background, 1 for tubular structures
 */
void orion_segmentation_method_occen( orion_segmentation_param* param ) {
	/* TODO
	 * Step 1: Select a training set of background points
	 *
	 * Refactor: readNegativeSamples
	 *
	 * call segmentation/laplacian-negative-samples/background.c
	 */

	/* TODO
	 * Step 2: Extract local shape information (features)
	 *
	 * Refactor: getFeatures
	 */

	/* TODO
	 * Step 3: Learn discriminant function
	 *
	 * Refactor: compute2D_DiscrimantFunction
	 */
	/* TODO
	 * Step 4: Segment neurons
	 *
	 * Refactor: see ORION3_Dendrites
	 *
	 * percentage_threshold_intensity
	 */
	/* TODO
	 * Step 5: Post-process the segmentation result
	 */
}

orion_segmentation_method_occen_set_default_param( orion_segmentation_param* param ) {
	orion_segmentation_param_set_default_scales( param );
}
