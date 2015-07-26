#include <stdlib.h>
#include <tap/basic.h>

#include "container/array.h"

int main() {
	plan( 1 + 2 + 1 + 3 );

	array_int* arr = array_new_int(3);

	/* 1 test */
	ok( arr != NULL, "integer array has been created");

	/* 2 tests */
	is_int( array_capacity_int(arr), 3, "array capacity is correct" );
	is_int( array_length_int(arr), 0, "array starts out empty" );

	array_add_int( arr, 7);
	array_add_int( arr, 8);
	array_add_int( arr, 9);

	/* 1 test */
	is_int( array_length_int(arr), 3, "added three elements" );

	/* 3 tests */
	is_int( array_get_int( arr, 0 ), 7, "1st element");
	is_int( array_get_int( arr, 1 ), 8, "2nd element");
	is_int( array_get_int( arr, 2 ), 9, "3rd element");

	array_add_int( arr, 42);

	return EXIT_SUCCESS;
}
