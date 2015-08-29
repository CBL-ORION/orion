#include <stdlib.h>
#include <tap/basic.h>

#include "integration/itk/itk.hxx"
#include "io/format/mhd.h"

int main(void) {
	plan(2);

	ndarray3* n = orion_read_mhd("test-data/DIADEM/NPF/NPF023/NPF023.mhd");

	array_ndarray3* frangi = orion_filter_method_frangi(n, 3.0);
	/* TODO */

	return EXIT_SUCCESS;
}
