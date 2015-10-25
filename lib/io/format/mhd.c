#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "io/format/mhd.h"
#include "io/path/path.h"
#include "io/util/util.h"

#include "util/likely.h"

/* See also: orion_mhd_datatype */
#undef ENUM
/* NOTE _ENUM_OPT_VAL is not used in this macro */
#define ENUM(_ENUM_NAME, _ENUM_OPT_VAL, _ENUM_TYPE) \
	[_ENUM_NAME] = STRINGIZE(_ENUM_NAME),
const char* orion_mhd_datatype_string[] = {
#include "io/format/mhd_datatype_table.h"

	"" /* last element */
};
#undef ENUM


/* Parses a string expression and returns a boolean:
 *
 * - If the string is "True", returns true.
 * - If the string is "False", returns false.
 */
bool orion_string_True_False_to_bool(const char* bool_string_rep) {
	if( 0 == strcmp("True", bool_string_rep) ) {
		return true;
	} else if( 0 == strcmp("False", bool_string_rep) ) {
		return false;
	} else {
		die("Invalid data for boolean. Expected \"True\" or \"False\", but got \"%s\"", bool_string_rep);
	}
	return false;
}

/* Parses a string with the name of a datatype value (e.g., "MET_USHORT") and
 * returns the corresponding `orion_mhd_datatype` enum value.
 *
 * Returns -1 if a corresponding `orion_mhd_datatype` is not found.
 */
orion_mhd_datatype orion_mhd_datatype_parse_string( const char* dt_string_rep ) {
	for( int met_datatype_idx = MET_DATATYPE_ENUM_FIRST;
			met_datatype_idx <= MET_DATATYPE_ENUM_LAST;
			met_datatype_idx++ ) {
		/*[>DEBUG<]printf("[%d] = %s\n", met_datatype_idx,
				orion_mhd_datatype_string[met_datatype_idx]);*/
		if( 0 == strcmp( dt_string_rep, orion_mhd_datatype_string[met_datatype_idx]) ) {
			 return met_datatype_idx;
		}
	}
	return -1; /* invalid */
}

/* Cast the input_buffer data to the type specified by meta->ElementType then
 * cast each of the values to pixel_type and returns a new buffer of type
 * pixel_type*.
 */
pixel_type* orion_mhd_cast_buffer( void* input_buffer, orion_mhd_metadata* meta ) {
	pixel_type* output_buffer;
	size_t elements = orion_mhd_meta_number_of_elements(meta);
	NEW_COUNT(output_buffer, pixel_type, elements);

#undef ENUM
/* create a case for each entry */
#define ENUM(_ENUM_NAME, _ENUM_OPT_VAL, _ENUM_TYPE) \
		case _ENUM_NAME: \
			{ \
				_ENUM_TYPE* cast_buffer = (_ENUM_TYPE*)input_buffer; \
				for( size_t idx = 0; idx < elements; idx++ ) { \
					output_buffer[idx] = (pixel_type)cast_buffer[idx]; \
				} \
				return output_buffer; \
			}

	switch( meta->ElementType ) {
#include "io/format/mhd_datatype_table.h"
		default:
			{
				die("Casting from orion_mhd_datatype ElementType = %d not implemented",
						meta->ElementType);
			}
	}
#undef ENUM


	return NULL;
}



/* Refactor: RAWfromMHD, WriteRAWandMHD */
orion_mhd_metadata* orion_read_mhd_metdata( char* mhd_filename ) {
	FILE* mhd_fh;
	char buffer[ORION_IO_MHD_BUFFER_SZ];
	char key_buffer[ORION_IO_MHD_BUFFER_SZ];
	char value_buffer[ORION_IO_MHD_BUFFER_SZ];
	orion_mhd_metadata* meta;
	if( NULL == ( mhd_fh = fopen( mhd_filename, "r" ) ) ) {
		die("Could not open MHD file %s", mhd_filename);
	}

	NEW(meta, orion_mhd_metadata);
	meta->DimSize = array_new_int(3);
	meta->ElementSpacing = array_new_float(3);
	meta->ElementType = -1;

	safe_malloc_and_strcpy( &(meta->_filename), mhd_filename);

	while( !feof( mhd_fh ) ) {
		memset(buffer, 0, ORION_IO_MHD_BUFFER_SZ*sizeof(char));
		memset(key_buffer, 0, ORION_IO_MHD_BUFFER_SZ*sizeof(char));
		memset(value_buffer, 0, ORION_IO_MHD_BUFFER_SZ*sizeof(char));

		orion_freadline(mhd_fh, buffer);
		/*[>DEBUG<]printf("%s\n", buffer);*/

		/* extract out key and value from line */
		sscanf(buffer, "%[^ ] = %[^\n]\n", key_buffer, value_buffer);

		/*[>DEBUG<]printf("-> %s <=> %s\n", key_buffer, value_buffer);*/
		       if( 0 == strcmp("ObjectType", key_buffer)             ) {
			/* Value [Str] (e.g., "Image") */
			safe_malloc_and_strcpy( &(meta->ObjectType), value_buffer);
		} else if( 0 == strcmp("NDims", key_buffer)                  ) {
			/* Value [size_t] (e.g., 3) */
			size_t ndims;
			sscanf(value_buffer, SIZE_T_FORMAT_SPEC, &ndims);
			meta->NDims = ndims;
		} else if( 0 == strcmp("BinaryData", key_buffer)             ) {
			/* Value [Boolean string] */
			meta->BinaryData =
				orion_string_True_False_to_bool(value_buffer);
		} else if( 0 == strcmp("BinaryDataByteOrderMSB", key_buffer) ) {
			/* Value [Boolean] */
			meta->BinaryDataByteOrderMSB =
				orion_string_True_False_to_bool(value_buffer);
		} else if( 0 == strcmp("ElementSpacing", key_buffer)         ) {
			/* Value[ array_float[Ndim] ] */
			orion_parse_sequence_float(value_buffer, &(meta->ElementSpacing));
		} else if( 0 == strcmp("DimSize", key_buffer)                ) {
			/* Value [ array_int[Ndim] ] */
			orion_parse_sequence_int(value_buffer, &(meta->DimSize));
		} else if( 0 == strcmp("ElementType", key_buffer)            ) {
			/* Value [orion_mhd_datatype] (e.g., "MET_USHORT") */
			meta->ElementType = orion_mhd_datatype_parse_string(value_buffer);
		} else if( 0 == strcmp("ElementDataFile", key_buffer)        ) {
			/* Value [Str] (e.g. "NPF023.raw") */
			safe_malloc_and_strcpy( &(meta->ElementDataFile), value_buffer );
		}
	}

	fclose(mhd_fh);

	return meta;
}

void orion_mhd_metadata_free(orion_mhd_metadata* meta) {
	if( meta->ObjectType )
		free(meta->ObjectType);
	if( meta->ElementDataFile )
		free(meta->ElementDataFile);
	array_free_int(meta->DimSize);
	array_free_float(meta->ElementSpacing);

	free( meta->_filename );

	free(meta);
}

ndarray3* orion_read_mhd(char* mhd_filename) {
	/* read the mhd file */
	orion_mhd_metadata* meta = orion_read_mhd_metdata( mhd_filename );

	if( unlikely(meta->NDims != 3) ) {
		die("the MetaInfo file %s is not a 3D volume. Expected NDims = 3, got NDims = " SIZE_T_FORMAT_SPEC ,
				meta->_filename,
				meta->NDims);
	}

	/* calculate the size of the buffer for holding the data and allocate
	 * the space */
	size_t bytes_to_read = orion_mhd_raw_byte_length( meta );
	void* raw_buffer;
	NEW_COUNT(raw_buffer, int8_t, bytes_to_read);

	/* find the path to the raw file using the ElementDataFile key */
	orion_filepath* mhd_file_fp = orion_filepath_new_from_string( meta->_filename );
	orion_filepath* raw_file_fp = orion_filepath_new_from_string(meta->ElementDataFile);
	orion_filepath* path_to_raw_fp = orion_filepath_sibling( mhd_file_fp, raw_file_fp );

	/*[>DEBUG<]orion_filepath_dump( mhd_file_fp );*/
	/*[>DEBUG<]orion_filepath_dump( raw_file_fp );*/
	/*[>DEBUG<]orion_filepath_dump( path_to_raw_fp );*/
	char* path_to_raw = orion_filepath_to_string(path_to_raw_fp);

	/* open the raw file */
	FILE* raw_file_fh = fopen(path_to_raw, "r");
	if( !raw_file_fh ) {
		die("Could not open ElementDataFile (%s) of the MetaInfo format file %s. Expected the file to be located at %s.",
				meta->ElementDataFile,
				mhd_filename,
				path_to_raw);
	}
	fread(raw_buffer, sizeof(int8_t), bytes_to_read, raw_file_fh);

	/* cast to pixel_type */
	pixel_type* buffer = orion_mhd_cast_buffer( raw_buffer, meta );

	free(raw_buffer);

	/* wrap the buffer and use the dimensions from the MetaInfo metadata */
	ndarray3* n = ndarray3_buffer( buffer,
			array_get_int(meta->DimSize, 0),
			array_get_int(meta->DimSize, 1),
			array_get_int(meta->DimSize, 2) );

	/* set ElementSpacing metadata */
	n->has_spacing = true;
	for( int i = 0; i < meta->NDims; i++ ) {
		n->spacing[i] = array_get_float( meta->ElementSpacing, i );
	}

	orion_filepath_free( mhd_file_fp );
	orion_filepath_free( raw_file_fp );
	orion_filepath_free( path_to_raw_fp );
	free( path_to_raw );

	orion_mhd_metadata_free(meta);

	fclose(raw_file_fh);

	return n;
}

size_t orion_mhd_meta_number_of_elements( orion_mhd_metadata* meta ) {
	size_t elements = 1;
	for( int i = 0; i < meta->NDims; i++ ) {
		elements *= array_get_int( meta->DimSize, i );
	}
	return elements;
}

size_t orion_mhd_raw_byte_length( orion_mhd_metadata* meta ) {
	return orion_mhd_element_sizeof( meta->ElementType )
		* orion_mhd_meta_number_of_elements( meta );
}

size_t orion_mhd_element_sizeof( orion_mhd_datatype dtype ) {

#undef ENUM
/* create a case for each entry */
#define ENUM(_ENUM_NAME, _ENUM_OPT_VAL, _ENUM_TYPE) \
		case _ENUM_NAME: return sizeof(_ENUM_TYPE);
	switch( dtype ) {
#include "io/format/mhd_datatype_table.h"
		default:
			{
				die("Unknown orion_mhd_datatype dtype = %d not implemented",
						dtype);
			}
	}
#undef ENUM
	return 0;
}
