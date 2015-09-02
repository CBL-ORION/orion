#include "io/util/util.h"

int orion_freadline(FILE* fh, char* buffer) {
	return fscanf(fh, "%[^\r\n]\n", buffer);
}

/* Parses a sequence of integer numbers and adds them to an `array_int`
 * container.
 *
 * If `arr_ptr` is NULL, allocates a new `array_int`.
 *
 * Returns the `array_int` in which the numbers have been added.
 */
array_int* orion_parse_sequence_int(const char* buffer, array_int** arr_ptr) {
	array_int* arr;
	if( !arr_ptr ) {
		/* initialise if NULL */
		*arr_ptr = array_new_int(3);
	}
	arr = *arr_ptr;

	/* read in each int out of the buffer */
	const char* sscanf_buffer = buffer;
	int sscanf_count = -1;
	int buffer_offset = 0; /* not size_t, used in %n */
	int num = 0;
	while( 0 != ( sscanf_count = sscanf(sscanf_buffer, "%d%n", &num, &buffer_offset) ) ) {
		if( sscanf_count < 1 )
			break;
		sscanf_buffer += buffer_offset;
		array_add_int( arr, num );
	}
	return arr;
}

/* Parses a sequence of floating point numbers and adds them to an
 * `array_float` container.
 *
 * If `arr_ptr` is NULL, allocates a new `array_float`.
 *
 * Returns the `array_float` in which the numbers have been added.
 */
array_float* orion_parse_sequence_float(const char* buffer, array_float** arr_ptr) {
	array_float* arr;
	if( !arr_ptr ) {
		/* initialise if NULL */
		*arr_ptr = array_new_float(3);
	}
	arr = *arr_ptr;

	/* read in each float out of the buffer */
	const char* sscanf_buffer = buffer;
	int sscanf_count = -1;
	int buffer_offset = 0; /* not size_t, used in %n */
	float num = 0.0;
	while( 0 != ( sscanf_count = sscanf(sscanf_buffer, "%f%n", &num, &buffer_offset) ) ) {
		if( sscanf_count < 1 )
			break;
		sscanf_buffer += buffer_offset;
		array_add_float( arr, num );
	}
	return arr;
}
