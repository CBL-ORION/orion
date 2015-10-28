/*
 * Refactor: settingDefaultParameters
 */
#include "kitchen-sink/01_Segmentation/dendrites_main/settingDefaultParameters.h"

#include <math.h>

#define ORION_SEGMENTATION_PERCENTAGE_THRESHOLD_INTENSITY_DEFAULT_SINGLE_SCALE 1.5
#define ORION_SEGMENTATION_PERCENTAGE_THRESHOLD_INTENSITY_DEFAULT_MULTISCALE 0.9
#define ORION_SEGMENTATION_BINS_DEFAULT 500
#define ORION_SEGMENTATION_TRAINING_DEFAULT 0.999
#define ORION_SEGMENTATION_THRESHOLD_DEFAULT 0.5

void orion_settingDefaultParameters( orion_segmentation_param* param ) {
	if( 0 == array_length_float( param->scales ) ) {
		orion_segmentation_param_set_default_scales( param );
	}

	param->multiscale = array_length_float( param->scales ) > 1;

	if( !param->has_release ) {
		param->release = false;
	}

	if( !param->has_apply_log ) {
		param->apply_log = false;
	}

	if( !param->has_training ) {
		param->training = ORION_SEGMENTATION_TRAINING_DEFAULT;
	}

	if( !param->has_threshold ) {
		param->threshold = ORION_SEGMENTATION_THRESHOLD_DEFAULT;
	}

	if( !param->has_min_conn_comp_to_remove) {
		if( param->multiscale ) {
			float64 max_scale = -INFINITY;
			for( int idx = 0; idx < array_length_float( param->scales ); idx++  ) {
				if( max_scale < array_get_float( param->scales, idx ) ) {
					max_scale = array_get_float( param->scales, idx );
				}
			}

			param->min_conn_comp_to_remove = (uint32_t)pow(2*max_scale, 3);
		} else {
			float64 first_sigma = array_get_float( param->scales, 0 );
			param->min_conn_comp_to_remove = (uint32_t)
				round( ceil( pow(4*first_sigma,3) ) );
		}
	}

	if( !param->has_percentage_threshold_intensity ) {
		if( param->multiscale ) {
			orion_segmentation_param_set_percentage_threshold_intensity(param,
					ORION_SEGMENTATION_PERCENTAGE_THRESHOLD_INTENSITY_DEFAULT_MULTISCALE);
		} else {
			orion_segmentation_param_set_percentage_threshold_intensity(param,
					ORION_SEGMENTATION_PERCENTAGE_THRESHOLD_INTENSITY_DEFAULT_SINGLE_SCALE);
		}
	}

	if( !param->has_bins ) {
		orion_segmentation_param_set_bins(param, ORION_SEGMENTATION_BINS_DEFAULT);
	}

}
