#include "param/orion3.h"

orion3_param* orion3_param_new() {
	orion3_param* param;

	NEW( param, orion3_param );

	param->scales = array_new_float(10);
	param->path_to_volume_directory = NULL;
	param->volume_names = array_new_str(1);
	param->remove_pipette = false;
	param->report_filename = NULL;
	param->has_registration_parameters_filename = false;
	param->has_starting_coordinate = false;

	return param;
}

void orion3_param_free( orion3_param* param ) {
	array_free_str(param->volume_names);
	array_free_float(param->scales);
	free(param);
}

void orion3_param_dump( orion3_param* param ) {
	fprintf(stderr, "orion3_param %p\n", param);

	fprintf(stderr, "Scales:\n");
	array_dump_float(param->scales);

	fprintf(stderr, "Path to volume directory: %s\n", param->path_to_volume_directory);

	fprintf(stderr, "Volumes:\n");
	array_dump_str(param->volume_names);
}
