/* TODO
 *
 * Refactor: ORION3_Dendrites
 */

#include "param/segmentation.h"
#include "ndarray/ndarray3.h"

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/readNegativeSamples.h"

void orion_ORION3_Dendrites(orion_segmentation_param* param, ndarray3* vol) {

	/* set the default parameters for the algorithm */
	orion_segmentation_param_set_default_scales( param );

	/*DEBUG*/orion_segmentation_param_dump( param );

	orion_readNegativeSamples(param, vol);

	WARN_UNIMPLEMENTED;
}
