#include "param/segmentation.h"

#include "container/array.h"

orion_segmentation_param* orion_segmentation_param_new() {
	orion_segmentation_param* param;
	NEW( param, orion_segmentation_param );
	param->scales = array_new_float( 10 );
	return param;
}

#define ATTR( NAME, TYPE ) \
	void orion_segmentation_param_set_ ## NAME ( orion_segmentation_param* param , TYPE new_ ## NAME ) { \
		param->NAME = new_ ## NAME; \
		param->has_ ## NAME  = true; \
	}
#include "segmentation_attr_table.h"
#undef ATTR


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
	if( param->scales ) {
		array_free_float(param->scales);
	}
	free(param);
}

void orion_segmentation_param_dump( orion_segmentation_param* param ) {
	fprintf(stderr, "orion_segmentation_param: %p\n", param);
	if( param->scales ) {
		fprintf(stderr, "\tscales (sigma): ");
		array_dump_float( param->scales );
	}
	fprintf(stderr, "\tmultiscale: %d\n", param->multiscale);

	if( param->has_percentage_threshold_intensity) fprintf(stderr, "\tpercentage_threshold_intensity: %f\n", param->percentage_threshold_intensity);
	if( param->has_release) fprintf(stderr, "\trelease: %d\n", param->release);
	if( param->has_apply_log) fprintf(stderr, "\tapply_log: %d\n", param->apply_log);
	if( param->has_training) fprintf(stderr, "\ttraining: %f\n", param->training);
	if( param->has_threshold) fprintf(stderr, "\tthreshold: %f\n", param->threshold);
	if( param->has_min_conn_comp_to_remove) fprintf(stderr, "\tmin_conn_comp_to_remove: %d\n", param->min_conn_comp_to_remove);
	if( param->has_bins) fprintf(stderr, "\tbins: %d\n", param->bins);

}
