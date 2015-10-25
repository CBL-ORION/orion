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
file_name = 'HeadMRVolume';
file_path = 'test-data/ITK/HeadMRVolume';
[n spacing] = RAWfromMHD(file_name,[],file_path);

scales = [ 1.50:0.25:2.50, 3, 4 ];
computeEigenvaluesGaussianFilter(file_path, file_name, 'SATO', 0, scales )
*/

int main(void) {
	const float64 eps = 1e-15;

	plan(3);

	ndarray3* n = orion_read_mhd("test-data/ITK/HeadMRVolume/HeadMRVolume.mhd");
	printf("orion_read_mhd: sum(n) = %f\n", ndarray3_sum_over_all_float64(n));
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

	size_t r_len = array_length_orion_eig_feat_result(r);

	/*[>DEBUG<]for( size_t r_idx = 0; r_idx < r_len; r_idx++ ) {
		orion_eig_feat_result* e = array_get_orion_eig_feat_result(r, r_idx);
		ndarray3* n_e = array_get_ndarray3(e->eig_feat,0);
		printf("i = %d; scale = %f; nd = %d; with sum for first = %f\n",
				r_idx,
				array_get_orion_eig_feat_result(r, r_idx)->scale,
				array_length_ndarray3(e->eig_feat),
				ndarray3_sum_over_all_float64(n_e)
				);
		printf("n[0,0,0] = %f\n",
				ndarray3_get(n_e, 0,0,0)
				);
		ndarray3_dump(n_e);
	}*/

	is_int( array_length_float(scales)  ,  array_length_orion_eig_feat_result(r), "there are as many results as there are scales");

	orion_eig_feat_result* first_result = array_get_orion_eig_feat_result(r,0);
	is_double( array_get_float(scales,0), first_result->scale, 0, "the first scale is recorded in the result as expected");

	ndarray3* first_result_first_n = array_get_ndarray3(first_result->eig_feat,0);
	ok( ndarray3_is_same_size(n, first_result_first_n), "the size of the returned ndarray3 is the same");




	for( size_t r_idx = 0; r_idx < r_len; r_idx++ ) {
		orion_eig_feat_result* e = array_get_orion_eig_feat_result(r, r_idx);
		orion_eig_feat_result_free(e);
	}
	array_free_orion_eig_feat_result(r);
	array_free_float(scales);
	ndarray3_free(n);

	return EXIT_SUCCESS;
}
