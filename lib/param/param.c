#include "param/param.h"
#include "container/array.h"

orion_parameters* orion_parameters_new() {
	orion_parameters* param;
	NEW( param, orion_parameters );
	param->scales = array_new_float( 10 );
	return NULL;
}

orion_parameters_set_default_scales( orion_parameters* param ) {
	array_resize_float( param->scale, 10 );
	array_add_float( param->scale, 1.50 );
	array_add_float( param->scale, 1.75 );
	array_add_float( param->scale, 2.00 );
	array_add_float( param->scale, 2.25 );
	array_add_float( param->scale, 2.50 );
	array_add_float( param->scale, 3.00 );
	array_add_float( param->scale, 4.00 );
}

void orion_parameters_free(orion_parameters* param) {
	free(param->scales);
}
