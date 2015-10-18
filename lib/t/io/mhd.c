#include <stdlib.h>
#include <string.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "ndarray/ndarray3.h"
#include "io/format/mhd.h"

int main(void) {
	const float64 eps = 1e-15;
	plan(4 + 5 + 5);

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
		/* 5 tests */
		ndarray3* vol = orion_read_mhd( mhd_file );
		ok( NULL != vol, "reading the MetaInfo file gives a non-NULL ndarray");

		/* check the size */
		is_int( 1024, vol->sz[0], "1st dim is correct size");
		is_int( 1024, vol->sz[1], "2nd dim is correct size");
		is_int(   57, vol->sz[2], "3rd dim is correct size");

		/* find the sum to expect by reading in the data:
		 *
		 * ../test/sum-of-an-metainfo-volume/SumMetaInfoVol test-data/DIADEM/NPF/NPF023/NPF023
		 */
		is_double(   11952376197.0000L, ndarray3_sum_over_all_float64(vol), eps, "sum of the volume is as expected");

		ndarray3_free(vol);
	}

	{
		/* 5 tests */
		ndarray3* vol = orion_read_mhd( "test-data/ITK/HeadMRVolume/HeadMRVolume.mhd" );
		ok( NULL != vol, "reading the MetaInfo file gives a non-NULL ndarray");

		/* check the size */
		is_int( 48, vol->sz[0], "1st dim is correct size");
		is_int( 62, vol->sz[1], "2nd dim is correct size");
		is_int( 42, vol->sz[2], "3rd dim is correct size");

		/* find the sum to expect by reading in the data:
		 *
		 * ../test/sum-of-an-metainfo-volume/SumMetaInfoVol test-data/ITK/HeadMRVolume/HeadMRVolume
		 */
		is_double(   3058332.0000L, ndarray3_sum_over_all_float64(vol), 0, "sum of the volume is as expected");

		ndarray3_free(vol);
	}



	return EXIT_SUCCESS;
}
