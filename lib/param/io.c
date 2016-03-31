#include "param/io.h"

orion_io_param* orion_io_param_new() {
	orion_io_param* param;
	NEW( param, orion_io_param );
	param->input_filename = NULL;
	param->output_filename = NULL;
	param->orion3_config_filename = NULL;
	return param;
}

void orion_io_param_free(orion_io_param* param) {
	if(param->input_filename) { free(param->input_filename); }
	if(param->output_filename) { free(param->output_filename); }
	if(param->orion3_config_filename) { free(param->orion3_config_filename); }
	free(param);
}

void orion_io_param_dump( orion_io_param* param ) {
	fprintf(stderr, "orion_io_param: %p\n", param);
	if( param->input_filename )
		fprintf(stderr, "\tinput: %s\n", param->input_filename);
	if( param->output_filename )
		fprintf(stderr, "\toutput: %s\n", param->output_filename);
	if( param->orion3_config_filename )
		fprintf(stderr, "\torion3_config: %s\n", param->orion3_config_filename);
}
