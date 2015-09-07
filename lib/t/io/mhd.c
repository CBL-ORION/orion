#include <stdlib.h>
#include <string.h>
#include <tap/basic.h>

#include "ndarray/ndarray3.h"
#include "io/format/mhd.h"

int main(void) {
	plan(4 + 4);

	char* mhd_file = "test-data/DIADEM/NPF/NPF023/NPF023.mhd";

	{
		/* 4 tests */
		orion_mhd_metadata* meta = orion_read_mhd_metdata( mhd_file );

		is_string( "NPF023.raw", meta->ElementDataFile, "the data file is right" );
		is_int(3, meta->NDims, "is a 3D volume" );
		is_int(3, array_length_int(meta->DimSize), "DimSize is of length 3" );
		is_int( MET_USHORT, meta->ElementType, "ElementType is correctly parsed");

		orion_mhd_metadata_free(meta);
	}

	{
		/* 4 tests */
		ndarray3* vol = orion_read_mhd( mhd_file );
		ok( NULL != vol, "reading the MetaInfo file gives a non-NULL ndarray");

		/* check the size */
		is_int( 1024, vol->sz[0], "1st dim is correct size");
		is_int( 1024, vol->sz[1], "2nd dim is correct size");
		is_int(   57, vol->sz[2], "3rd dim is correct size");

		ndarray3_free(vol);
	}




	return EXIT_SUCCESS;
}
