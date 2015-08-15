#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

#include "orion3-config-parser/parser.h"

int main(void) {
	plan( 1 + 2 + 2 );

	char* path_to_input = "test-data/DIADEM/NPF/Input_NPF023_D.txt";
	orion3_param* p = orion3_param_read_input_file(path_to_input);

	/*orion3_param_dump( p );*/

/* 1 test */
	ok( p != NULL, "orion3 parameters non-NULL" );

/* 2 tests */
	is_int(5, array_length_float(p->scales), "There are 5 scales");
	is_double(16.0, array_get_float(p->scales, 0), 1e-10, "The first of which is 16.0");

/* 2 tests */
	is_int(1, array_length_str(p->volume_names), "There is 1 volume to process");
	ok( 0 == strcmp( "NPF023", array_get_str(p->volume_names, 0) ), "and has the expected volume name" );

	return EXIT_SUCCESS;
}
