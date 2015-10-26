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
sums = zeros(size(scales));
idx = 1;
for s = scales;
	disp(sprintf('Calculating %g', s));
	ID_label = '';
	computeEigenvaluesGaussianFilter(file_path, file_name, s, 'SATO', 0, [] );

	% read in the first eigenvalue MetaImage file
	fn = [file_name ID_label '.EigVal1.Sigma.' num2string(s) ];
	v =  RAWfromMHD( fn, [], file_path );

	sums(idx) = sum( v(:) );
	idx = idx + 1;
end

% The sum of all the first eigenvalues.
% This is used below.
disp(sprintf('%.4f\n', sums))

*/

int main(void) {
	/* NOTE: really large epsilon. This is because we are summing and the
	 * the floating point rounding may effect the result when comparing with
	 * MATLAB data. */
	const float64 eps = 1;

	plan(3 + 1);

	ndarray3* n = orion_read_mhd("test-data/ITK/HeadMRVolume/HeadMRVolume.mhd");

	array_float* scales = array_new_float( 10 );
	/* taken from MATLAB `sums` variable above */
	array_float* sums = array_new_float( 10 );

	array_add_float( scales, 1.50 );array_add_float(sums, 208564.0312 );
	array_add_float( scales, 1.75 );array_add_float(sums, 269313.5000 );
	array_add_float( scales, 2.00 );array_add_float(sums, 334097.3750 );
	array_add_float( scales, 2.25 );array_add_float(sums, 381097.5938 );
	array_add_float( scales, 2.50 );array_add_float(sums, 404807.3125 );
	array_add_float( scales, 3.00 );array_add_float(sums, 421116.8125 );
	array_add_float( scales, 4.00 );array_add_float(sums, 438598.1875 );

	array_orion_eig_feat_result* r = orion_computeEigenvaluesGaussianFilter(n, EIG_FEAT_METHOD_SORT_SATO, false, scales);

	size_t r_len = array_length_orion_eig_feat_result(r);

	{/* 3 tests */
		/* sanity tests */
		is_int( array_length_float(scales)  ,  array_length_orion_eig_feat_result(r), "there are as many results as there are scales");

		orion_eig_feat_result* first_result = array_get_orion_eig_feat_result(r,0);
		is_double( array_get_float(scales,0), first_result->scale, 0, "the first scale is recorded in the result as expected");

		ndarray3* first_result_first_n = array_get_ndarray3(first_result->eig_feat,0);
		ok( ndarray3_is_same_size(n, first_result_first_n), "the size of the returned ndarray3 is the same");
	}

	{/* 1 test */
		bool all_sums_expect = true;
		for( size_t r_idx = 0; r_idx < r_len && all_sums_expect; r_idx++ ) {
			orion_eig_feat_result* e =
				array_get_orion_eig_feat_result(r, r_idx);

			/* first eigenvalue */
			ndarray3* n_e = array_get_ndarray3(e->eig_feat,0);

			all_sums_expect &= fabs(
				ndarray3_sum_over_all_float64(n_e)
				   - array_get_float(sums, r_idx)
				) < eps;

			/*[>DEBUG<]printf("i = %d; scale = %f; with sum for first = %f and expect %f\n",
					r_idx,
					array_get_orion_eig_feat_result(r, r_idx)->scale,
					ndarray3_sum_over_all_float64(n_e),
					array_get_float(sums, r_idx)
					);*/
		}

		ok( all_sums_expect, "The sum of the first eigenvalue is as is expected");
	}



	for( size_t r_idx = 0; r_idx < r_len; r_idx++ ) {
		orion_eig_feat_result* e = array_get_orion_eig_feat_result(r, r_idx);
		orion_eig_feat_result_free(e);
	}
	array_free_orion_eig_feat_result(r);
	array_free_float(scales);
	array_free_float(sums);
	ndarray3_free(n);

	return EXIT_SUCCESS;
}
