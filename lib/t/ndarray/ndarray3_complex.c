#include <stdlib.h>
#include <stdio.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "ndarray/ndarray3_complex.h"

int main(void) {
	plan(1);

	ndarray3_complex* n = ndarray3_complex_new( 2, 2, 2 );

	ndarray3_complex_set( n, 0, 0, 0, 1 + 2 * I );

	complex_pixel_type z = ndarray3_complex_get(n, 0,0,0);

	diag( "%f + %fi", creal(z), cimag(z) );

	ok(z == 1 + 2 * I, "Got the expected complex value ( 1 + 2i )");

	ndarray3_complex_free(n);

	return EXIT_SUCCESS;
}
