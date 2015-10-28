#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "kitchen-sink/01_Segmentation/dendrites_main/settingDefaultParameters.h"

/*
% MATLAB

p = []; p.sigma = [2]; settingDefaultParameters(p, 'test-data/DIADEM/NPF/NPF023', 'NPF023')

p = []; p.sigma = [2 8]; settingDefaultParameters(p, 'test-data/DIADEM/NPF/NPF023', 'NPF023')

*/
int main(void) {
	plan(8 * 2);

	{/* 8 tests */
		/* single scale parameters */
		orion_segmentation_param* param_ss =
			orion_segmentation_param_new();
		array_add_float( param_ss->scales, 2 );
		orion_settingDefaultParameters(param_ss);

		is_int( false    , param_ss->multiscale, "single scale" );
		is_double(1.5    , param_ss->percentage_threshold_intensity, 0, "%% threshold intensity");
		is_int( false    , param_ss->release, "is not release" );
		is_int( false    , param_ss->apply_log, "do not apply log" );
		is_double( 0.9990, param_ss->training, 0, "training" );
		is_double( 0.5000, param_ss->threshold, 0, "threshold");
		is_int( 512 , param_ss->min_conn_comp_to_remove, "min_c");
		is_int( 500 , param_ss->bins, "bins");

		orion_segmentation_param_free(param_ss);
		/* output from MATLAB */
                          /*sigma: [2 3]
                        multiscale: 0
    percentage_threshold_intensity: 1.5000
                           release: 0
                         apply_log: 0
                          training: 0.9990
                         threshold: 0.5000
                             min_c: 512
                              bins: 500
                     folder_output: 'test-data/DIADEM/NPF/NPF023'
              file_ID_segmentation: ''
                      delete_files: 1
                       show_images: 0*/
	}

	{/* 8 tests */
		/* multiscale parameters */
		orion_segmentation_param* param_ms =
			orion_segmentation_param_new();
		array_add_float( param_ms->scales, 2 );
		array_add_float( param_ms->scales, 8 );

		orion_settingDefaultParameters(param_ms);

		is_int( true     , param_ms->multiscale, "multiscale" );
		is_double(0.9000 , param_ms->percentage_threshold_intensity, 0, "%% threshold intensity");
		is_int( false    , param_ms->release, "is not release" );
		is_int( false    , param_ms->apply_log, "do not apply log" );
		is_double( 0.9990, param_ms->training, 0, "training" );
		is_double( 0.5000, param_ms->threshold, 0, "threshold");
		is_int( 4096 , param_ms->min_conn_comp_to_remove, "min_c");
		is_int( 500 , param_ms->bins, "bins");


		orion_segmentation_param_free(param_ms);
		/* output from MATLAB */
                        /*multiscale: 1
                             min_c: 4096
                           release: 0
                         apply_log: 0
                          training: 0.9990
                         threshold: 0.5000
    percentage_threshold_intensity: 0.9000
                              bins: 500
                     folder_output: 'test-data/DIADEM/NPF/NPF023'
              file_ID_segmentation: ''
                      delete_files: 1
                       show_images: 0*/
	}


	return EXIT_SUCCESS;
}
