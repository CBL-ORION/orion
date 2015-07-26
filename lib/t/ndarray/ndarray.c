#include <stdlib.h>
#include <tap/basic.h>

#include "ndarray/ndarray3.h"

int main(void) {
	plan(4);
	ndarray3* nd_test = ndarray3_new(3, 4, 5);

	ok(nd_test != NULL, "array created");

	is_int(nd_test->sz[0], 3, "size of first dim is correct");
	is_int(nd_test->sz[1], 4, "size of second dim is correct");
	is_int(nd_test->sz[2], 5, "size of second dim is correct");

	return EXIT_SUCCESS;
}
