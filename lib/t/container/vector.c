#include <stdlib.h>
#include <tap/basic.h>

#include "container/vector.h"

int main() {
	plan( 1 + 1 + 3 );

	vector_int* vec = vector_new_int(3);

/* 1 test */
	ok( vec != NULL, "integer vector has been created");

/* 1 tests */
	is_int( 3, vector_length_int(vec), "vector has length 3" );

	vector_set_int( vec, 0, 7);
	vector_set_int( vec, 1, 8);
	vector_set_int( vec, 2, 9);

/* 3 tests */
	is_int( 7, vector_get_int( vec, 0 ), "1st element");
	is_int( 8, vector_get_int( vec, 1 ), "2nd element");
	is_int( 9, vector_get_int( vec, 2 ), "3rd element");

	return EXIT_SUCCESS;
}
