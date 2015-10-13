#include <stdlib.h>
#include <tap/basic.h>

#include "ndarray/ndarray3.h"

int main(void) {
	plan(4);
	ndarray3* nd_test = ndarray3_new(3, 4, 5);

	ok(nd_test != NULL, "array created");

	is_int(3, nd_test->sz[0], "size of first dim is correct");
	is_int(4, nd_test->sz[1], "size of second dim is correct");
	is_int(5, nd_test->sz[2], "size of second dim is correct");

	ndarray3_free( nd_test );

	return EXIT_SUCCESS;
}
