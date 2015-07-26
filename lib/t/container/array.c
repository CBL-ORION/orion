#include <stdlib.h>
#include <tap/basic.h>

#include "container/array.h"

int main() {
	plan(3);

	array_int* arr = array_new_int(3);

	ok( arr != NULL, "integer array has been created");

	is_int( array_capacity_int(arr), 3, "array capacity is correct" );
	is_int( array_length_int(arr), 0, "array starts out empty" );

	return EXIT_SUCCESS;
}
