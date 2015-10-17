#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include <math.h>
#include "io/format/mhd.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeEigenvaluesGaussianFilter.h"
#include "param/segmentation.h"

/*
% MATLAB

*/

int main(void) {
	const float64 eps = 1e-15;

	plan(3);

	ndarray3* n = orion_read_mhd("test-data/ITK/HeadMRVolume/HeadMRVolume.mhd");
	array_float* scales = array_new_float( 10 );
	array_add_float( scales, 1.50 );
	array_add_float( scales, 1.75 );
	array_add_float( scales, 2.00 );
	array_add_float( scales, 2.25 );
	array_add_float( scales, 2.50 );
	array_add_float( scales, 3.00 );
	array_add_float( scales, 4.00 );

	array_orion_eig_feat_result* r = orion_computeEigenvaluesGaussianFilter(n, EIG_FEAT_METHOD_SORT_SATO, false, scales);

	return EXIT_SUCCESS;
}
