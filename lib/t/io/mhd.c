#include <stdlib.h>
#include <tap/basic.h>

#include "ndarray/ndarray3.h"
#include "io/format/mhd.h"

int main(void) {
	plan(2);

	ndarray3* vol = orion_read_mhd( "test-data/DIADEM/NPF/NPF023/NPF023.mhd" );

	/* TODO check the size */


	return EXIT_SUCCESS;
}
