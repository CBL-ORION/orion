#include "param/segmentation.h"
#include "container/array.h"

orion_segmentation_param* orion_segmentation_param_new() {
	orion_segmentation_param* param;
	NEW( param, orion_segmentation_param );
	param->scales = array_new_float( 10 );
	param->percentage_threshold_intensity = ORION_SEGMENTATION_PERCENTAGE_THRESHOLD_INTENSITY_DEFAULT;
	return param;
}

void orion_segmentation_param_set_default_scales( orion_segmentation_param* param ) {
	array_resize_float( param->scales, 10 );
	array_add_float( param->scales, 1.50 );
	array_add_float( param->scales, 1.75 );
	array_add_float( param->scales, 2.00 );
	array_add_float( param->scales, 2.25 );
	array_add_float( param->scales, 2.50 );
	array_add_float( param->scales, 3.00 );
	array_add_float( param->scales, 4.00 );
}

void orion_segmentation_param_free(orion_segmentation_param* param) {
	free(param->scales);
	free(param);
}

void orion_segmentation_param_dump( orion_segmentation_param* param ) {
	fprintf(stderr, "orion_segmentation_param: %x\n", param);
	if( param->scales )
		array_dump_float( param->scales );
}
