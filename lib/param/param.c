#include "param/param.h"
#include "container/array.h"

orion_parameters* orion_parameters_new() {
	orion_parameters* param;
	NEW( param, orion_parameters );
	param->scales = array_new_float( 10 );
	return NULL;
}

void orion_parameters_free(orion_parameters* param) {
	free(param->scales);
}
