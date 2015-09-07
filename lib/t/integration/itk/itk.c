#include <stdlib.h>
#include <tap/basic.h>

#include "integration/itk/itk.hxx"
#include "io/format/mhd.h"

int main(void) {
	plan( 1 + 2 );

/* 1 test */
	ndarray3* n = orion_read_mhd("test-data/ITK/HeadMRVolume/HeadMRVolume.mhd");
	/*DEBUG*/ndarray3_dump( n );
	ok( NULL != n, "read in the raw data");


/* 2 tests */
	array_ndarray3* frangi = orion_filter_method_frangi(n, 3.0);
	ok( NULL != frangi, "Frangi filter returns non-NULL result" );
	is_int( 3, array_length_ndarray3(frangi),
			"the length of the Frangi array is 3");


	for( int idx = 0; idx < array_length_ndarray3(frangi); idx++ ) {
		ndarray3_free( array_get_ndarray3(frangi, idx) );
	}
	array_free_ndarray3( frangi );
	ndarray3_free(n);

	return EXIT_SUCCESS;
}
