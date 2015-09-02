#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "io/format/mhd.h"
#include "io/path/path.h"
#include "io/util/util.h"

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

	safe_malloc_and_strcpy( &(meta->_filename), mhd_filename);

	while( !feof( mhd_fh ) ) {
		memset(buffer, 0, ORION_IO_MHD_BUFFER_SZ*sizeof(char));
		memset(key_buffer, 0, ORION_IO_MHD_BUFFER_SZ*sizeof(char));
		memset(value_buffer, 0, ORION_IO_MHD_BUFFER_SZ*sizeof(char));

		orion_freadline(mhd_fh, buffer);
		printf("%s\n", buffer);

		sscanf(buffer, "%[^ ] = %[^\n]\n", key_buffer, value_buffer);
		printf("-> %s <=> %s\n", key_buffer, value_buffer);
		       if( 0 == strcmp("ObjectType", key_buffer)             ) {
			/* TODO Value [Str]
			 * "Image"
			 */
		} else if( 0 == strcmp("NDims", key_buffer)                  ) {
			/* TODO Value [size_t]
			 * e.g., 3
			 */
			size_t ndims;
			sscanf(value_buffer, SIZE_T_FORMAT_SPEC, &ndims);
			meta->NDims = ndims;
		} else if( 0 == strcmp("BinaryData", key_buffer)             ) {
			/* TODO Value [Boolean]
			 * "True", "False"
			 */
			meta->BinaryData =
				orion_string_True_False_to_bool(value_buffer);
		} else if( 0 == strcmp("BinaryDataByteOrderMSB", key_buffer) ) {
			/* TODO Value [Boolean]
			 * "True", "False"
			 */
			meta->BinaryDataByteOrderMSB =
				orion_string_True_False_to_bool(value_buffer);
		} else if( 0 == strcmp("ElementSpacing", key_buffer)         ) {
			/* TODO Value[ array_float[Ndim] ]
			 */
			orion_parse_sequence_float(value_buffer, &(meta->ElementSpacing));
		} else if( 0 == strcmp("DimSize", key_buffer)                ) {
			/* TODO Value [ array_int[Ndim] ]
			 */
			orion_parse_sequence_int(value_buffer, &(meta->DimSize));
		} else if( 0 == strcmp("ElementType", key_buffer)            ) {
			/* TODO Value [orion_mhd_datatype]
			 * "MET_USHORT"
			 */
		} else if( 0 == strcmp("ElementDataFile", key_buffer)        ) {
			safe_malloc_and_strcpy( &(meta->ElementDataFile), value_buffer );
			/* TODO Value [Str]
			 * "NPF023.raw"
			 */
		}
	}

	return meta;
}

ndarray3* orion_read_mhd(char* mhd_filename) {
	/* read the mhd file */
	orion_mhd_metadata* meta = orion_read_mhd_metdata( mhd_filename );

	TODO( read the raw file wite same name in the same folder );
	size_t bytes_to_read = orion_mhd_raw_byte_length( meta );
	void* raw_buffer;
	NEW_COUNT(raw_buffer, int8_t, bytes_to_read);

	return NULL;
	char* raw_file = meta->ElementDataFile; /* TODO */
	FILE* raw_file_fh = fopen(raw_file, "r");
	if( !raw_file_fh ) {
		die("Could not open ElementDataFile (%s) of the MetaInfo format file", meta->ElementDataFile, mhd_filename);
	}
	fread(raw_buffer, sizeof(int8_t), bytes_to_read, raw_file_fh);

	WARN_UNIMPLEMENTED;
	return NULL;
}

size_t orion_mhd_raw_byte_length( orion_mhd_metadata* meta ) {
	size_t bytes = orion_mhd_element_size( meta->ElementType );
	for( int i = 0; i < meta->NDims; i++ ) {
		bytes *= array_get_int( meta->DimSize, i );
	}
	return bytes;
}

size_t orion_mhd_element_size( orion_mhd_datatype dtype ) {
	switch( dtype ) {
		case MET_UCHAR:  return sizeof( uint8_t);
		case MET_SHORT:  return sizeof(  int16_t);
		case MET_USHORT: return sizeof( uint16_t);
		case MET_ULONG:  return sizeof( uint32_t);
		case MET_UINT:   return sizeof( uint32_t);
		case MET_FLOAT:  return sizeof(float32 );
		case MET_DOUBLE: return sizeof(float64 );
	}
	return 0;
}
