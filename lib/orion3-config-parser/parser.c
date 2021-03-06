#include "orion3-config-parser/parser.h"
#include "io/util/util.h"

/* REFACTOR: readinformationOR3.m */
orion3_param* orion3_param_read_input_file(char* filename) {
	assert( filename != NULL ); /* the filename string is not a NULL pointer */
	char buffer[ORION_ORION3_CONFIG_PARSER_BUFFER_SZ];

	orion3_param* param = orion3_param_new();

	/* Open the file */
	LOG_INFO("Opening the file %s", filename);
	FILE* f = fopen(filename, "r");
	assert( f != NULL ); /* file was opened */

	/* The first line contains floats that are the scales to be used in the
	 * segmentation.
	 *
	 * Read into: `param->scales`.
	 *
	 * Read in a line of floats:
	 *
	 *     float_0 float_1 float_2
	 *
	 */
	{
		/* read in the first line into the buffer */
		orion_freadline(f, buffer);
		orion_parse_sequence_float( buffer, &(param->scales) );
	}

	/* The second line is the path to the volume.
	 *
	 * Read into: `param->path_to_volume_directory`
	 */
	{
		orion_freadline(f, buffer);
		safe_malloc_and_strcpy( &(param->path_to_volume_directory), buffer );
	}

	/* Read in non-numeric lines to get a list of files.
	 *
	 * Once a numeric line is reached, this is the end of the list of
	 * volumes to process. Next line is a boolean indicating whether or not
	 * to remove the pippette.
	 *
	 * Read into: `param->volume_names`.
	 */
	int scan_for_boolean = -1;
	{
		char* single_volume_name = NULL;
		do {
			orion_freadline(f, buffer);
			if( sscanf(buffer, "%d", &scan_for_boolean) ) {
				/* found an integer */
				break;
			}
			safe_malloc_and_strcpy( &single_volume_name, buffer );
			array_add_str(param->volume_names, single_volume_name );
		} while( 1 );
	}

	/* Read in numeric (0 or 1) for pipette removal
	 *
	 * Number indicates a boolean that indicates to remove pipette or not.
	 *
	 * Read into: `param->remove_pipette`.
	 */
	{
		param->remove_pipette = scan_for_boolean;
	}

	/* Read in string for report filename.
	 *
	 * Read into: `param->report_filename`.
	 */
	{
		orion_freadline(f, buffer);
		safe_malloc_and_strcpy( &(param->report_filename), buffer );
	}

	/* [optional]
	 * Read in filename of translation parameters. This is only read when
	 * there are more than one volumes to process.
	 *
	 * Read into:
	 *     `param->has_registration_parameters_filename`
	 *     `param->registration_parameters_filename`
	 */
	{
		TODO(Translation parameters);
		if( array_length_str(param->volume_names) > 1 ) {
			WARN_UNIMPLEMENTED;
			die("%s", "Does not support reading translation parameters for registration");
		}
	}

	/* Read in starting coordinates [MATLAB vector]
	 *
	 * Read into:
	 *     `param->has_starting_coordinate`
	 *     `param->starting_coordinate`
	 */
	{
		TODO(Starting coordinates);
	}

	/* finally, close the file */
	fclose(f);

	return param;
}
