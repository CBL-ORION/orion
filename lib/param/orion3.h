#ifndef PARAM_ORION3_H
#define PARAM_ORION3_H 1

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

	char* report_file_name;

	bool has_registration_parameters_file_name;
	char* registration_parameters_file_name;

	bool has_starting_coordinate;
	float starting_coordinate[3]; /* TODO should this be a size_t? */
} orion3_param;

#endif /* PARAM_ORION3_H */
