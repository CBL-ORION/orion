#include <stdlib.h>
#include <string.h>
#include <tap/basic.h>

#include "ndarray/ndarray3.h"
#include "io/format/mhd.h"

int main(void) {
	plan(3);

	char* mhd_file = "test-data/DIADEM/NPF/NPF023/NPF023.mhd";
	orion_mhd_metadata* meta = orion_read_mhd_metdata( mhd_file );

	is_string( "NPF023.raw", meta->ElementDataFile, "the data file is right" );
	is_int(3, meta->NDims, "is a 3D volume" );
	is_int(3, array_length_int(meta->DimSize), "DimSize is of length 3" );

	/*ndarray3* vol = orion_read_mhd(  );*/

	/* TODO check the size */


	return EXIT_SUCCESS;
}
