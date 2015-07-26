#include "param/param.h"

orion_parameters* orion_parameters_new() {
	WARN_UNIMPLEMENTED;
	orion_parameters* param;
	param->scales = array_new_float( 10 );
	return NULL;
}

void orion_parameters_free(orion_parameters* param) {
	free(param->scales);
}
