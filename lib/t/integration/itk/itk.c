#include <stdlib.h>
#include <tap/basic.h>

#include "integration/itk/itk.hxx"
#include "io/format/mhd.h"

int main(void) {
	plan( 1 + 1 );

	/*skip("rest of tests can not run without MetaInfo file reading");
	return EXIT_SUCCESS;*/

/* 1 test */
	ndarray3* n = orion_read_mhd("test-data/ITK/HeadMRVolume/HeadMRVolume.mhd");
	/*DEBUG*/ndarray3_dump( n );
	ok( NULL != n, "read the metainfo data");

/* 1 test */
	array_ndarray3* frangi = orion_filter_method_frangi(n, 3.0);
	ok( NULL != frangi, "Frangi filter returns non-NULL result" );
	TODO( test that the length of the frangi array is 3 );
	/* TODO */

	return EXIT_SUCCESS;
}
