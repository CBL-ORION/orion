#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "kitchen-sink/01_Segmentation/dendrites_main/ORION3_Dendrites.h"

#include "param/segmentation.h"
#include "io/format/mhd.h"

/*
% MATLAB

p.sigma = 2;
ORION3_Dendrites('test-data/DIADEM/NPF/NPF023', 'NPF023', p);

*/

int main(void) {
	const float64 eps = 1;

	plan(1);

	/* read in the volume to process */
	/*ndarray3* n = orion_read_mhd("test-data/DIADEM/NPF/NPF023/NPF023.mhd");*/
	ndarray3* n = orion_read_mhd("test-data/ITK/HeadMRVolume/HeadMRVolume.mhd");

	/* set up the parameters with sigma = 2 */
	orion_segmentation_param* param = orion_segmentation_param_new();
	array_add_float( param->scales, 2 );

	orion_ORION3_Dendrites( param, n );


	/* done */
	orion_segmentation_param_free(param);
	ndarray3_free(n);

	return EXIT_SUCCESS;
}
