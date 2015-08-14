#include "param/param.h"
#include "container/array.h"

orion_io_param* orion_io_param_new() {
	orion_io_param* param;
	NEW( param, orion_io_param );
	return param;
}

void orion_io_param_free(orion_io_param* param) {
	free(param->input_filename);
	free(param->output_filename);
	free(param);
}
