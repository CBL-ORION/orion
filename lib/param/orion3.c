#include "param/orion3.h"

void orion3_param_dump( orion3_param* param ) {
	fprintf(stderr, "Scales:\n");
	array_dump_float(param->scales);

	fprintf(stderr, "%s", param, param->path_to_volume_directory);

	TODO( dump the rest );
}
