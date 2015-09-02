#include <stdlib.h>
#include <string.h>
#include <tap/basic.h>

#include "io/path/path.h"

int main(void) {
	plan(1);

	char* fp_str_fwd_slash = "path/to/file.c";
	/*orion_filepath* fp_fwd_slash = orion_filepath_new_from_string(fp_str_fwd_slash);
	ok( fp_str_fwd_slash,
		orion_filepath_to_string(fp_fwd_slash),
		"the path created from a path with forward slashes remains the same" );*/



	return EXIT_SUCCESS;
}
