#ifndef PARAM_ORION3_H
#define PARAM_ORION3_H 1

#include <stdio.h>
#include <stdbool.h>

#include "container/array.h"

typedef struct {
	array_float* scales;     /* sigma */

	/* the actual volume will be the files:
	 *
	 *   - path_to_volume_directory / volume_name[n] / volume_name[n] . mhd
	 *   - path_to_volume_directory / volume_name[n] / volume_name[n] . raw
	 */
	char* path_to_volume_directory;

	array_str* volume_names;

	bool remove_pipette;

	char* report_filename;

	bool has_registration_parameters_filename;
	char* registration_parameters_filename;

	bool has_starting_coordinate;
	float starting_coordinate[3]; /* TODO should this be a size_t? */
} orion3_param;

extern void orion3_param_dump( orion3_param* param );

#endif /* PARAM_ORION3_H */
