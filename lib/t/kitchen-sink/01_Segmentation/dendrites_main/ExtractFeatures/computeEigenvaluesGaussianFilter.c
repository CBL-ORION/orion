#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include <math.h>
#include "io/format/mhd.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeEigenvaluesGaussianFilter.h"
#include "param/segmentation.h"
#include "ndarray/ndarray3.h"

/*
% MATLAB

*/

int main(void) {
	const float64 eps = 1e-15;

	plan(3);

	ndarray3* n = orion_read_mhd("test-data/ITK/HeadMRVolume/HeadMRVolume.mhd");
	/*[>DEBUG<]ndarray3_dump(n);*/

	array_float* scales = array_new_float( 10 );
	array_add_float( scales, 1.50 );
	array_add_float( scales, 1.75 );
	array_add_float( scales, 2.00 );
	array_add_float( scales, 2.25 );
	array_add_float( scales, 2.50 );
	array_add_float( scales, 3.00 );
	array_add_float( scales, 4.00 );

	array_orion_eig_feat_result* r = orion_computeEigenvaluesGaussianFilter(n, EIG_FEAT_METHOD_SORT_SATO, false, scales);

	for( size_t r_idx = 0; r_idx < array_length_orion_eig_feat_result(r); r_idx++ ) {
		orion_eig_feat_result* e = array_get_orion_eig_feat_result(r, r_idx);
		ndarray3* n = array_get_ndarray3(e->eig_feat,0);
		printf("i = %d; scale = %f; nd = %d\n", r_idx, array_get_orion_eig_feat_result(r, r_idx)->scale, array_length_ndarray3(e->eig_feat) );
		ndarray3_dump(n);
	}

	for( size_t r_idx = 0; r_idx < array_length_orion_eig_feat_result(r); r_idx++ ) {
		orion_eig_feat_result* e = array_get_orion_eig_feat_result(r, r_idx);
		orion_eig_feat_result_free(e);
	}
	array_free_orion_eig_feat_result(r);
	array_free_float(scales);
	ndarray3_free(n);

	return EXIT_SUCCESS;
}
