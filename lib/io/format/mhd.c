#include <stdio.h>

#include "io/format/mhd.h"
#include "io/path/path.h"

/* Refactor: RAWfromMHD, WriteRAWandMHD */
orion_mhd_metadata* orion_read_mhd_metdata( char* mhd_filename ) {
	FILE* mhd_fh;
	char buffer[ORION_IO_MHD_BUFFER_SZ];
	orion_mhd_metadata* meta;
	if( NULL == ( mhd_fh = fopen( mhd_filename, "r" ) ) ) {
		die("Could not open MHD file %s", mhd_filename);
	}

	NEW(meta, orion_mhd_metadata);

	while( !feof( mhd_fh ) ) {
		fscanf(mhd_fh, "%[^\n]\n", buffer);
	}
}

ndarray3* orion_read_mhd(char* mhd_filename) {
	orion_mhd_metadata* meta = orion_read_mhd_metdata( mhd_filename );


	TODO( read the mhd file );
	TODO( read the raw file wite same name in the same folder );

	WARN_UNIMPLEMENTED;
	return NULL;
}


