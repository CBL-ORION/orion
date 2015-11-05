#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/multiscaleLaplacianFilter.h"
#include "kitchen-sink/01_Segmentation/dendrites_main/settingDefaultParameters.h"
#include "container/array.h"
#include "io/format/mhd.h"

/*
% MATLAB
file_path = 'test-data/ITK/HeadMRVolume';
file_name = 'HeadMRVolume';
Lap = 0.66 ./ [ 1 2 3 4 ];
p.sigma = 0; p = settingDefaultParameters(p, file_path, file_name);
[l s] = multiscaleLaplacianFilter(file_path,file_name,Lap,p);

sprintf('%f', sum(l(:)))
% 1199656.000000
histc(s(:), unique(s))
% [ 21569 22746 32072 48605 ]
*/
int main(void) {
	plan(1);
	const float64 eps = 1e-10;

	/* read in the volume to process */
	ndarray3* n = orion_read_mhd("test-data/ITK/HeadMRVolume/HeadMRVolume.mhd");

	array_float* lap_scales = array_new_float(4);
	array_add_float( lap_scales, 0.66/1 );
	array_add_float( lap_scales, 0.66/2 );
	array_add_float( lap_scales, 0.66/3 );
	array_add_float( lap_scales, 0.66/4 );

	orion_segmentation_param* p =
		orion_segmentation_param_new();
	orion_settingDefaultParameters(p);

#if 1 /* stub */
	orion_multiscale_laplacian_output* r =
		orion_multiscaleLaplacianFilter( n, lap_scales, p );

	/* value take from MATLAB code above */
	is_double(1199656.000000, ndarray3_sum_over_all_float64( r->laplacian ), eps, "sum of Laplacian response is as expected" );
#endif

	orion_multiscale_laplacian_output_free(r);
	orion_segmentation_param_free(p);
	array_free_float(lap_scales);
	ndarray3_free(n);

	return EXIT_SUCCESS;
}
