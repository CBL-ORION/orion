#include <stdlib.h>
#include <string.h>
#include <tap/basic.h>

#include "io/path/path.h"

int main(void) {
	/* data */
	typedef struct {
		char* fp_path;
		char* fp_dir;
		char* fp_base;
	} path_test_spec;

	const size_t TEST_CASES = 2;
	path_test_spec fp_data[] = {
		{ "path/to/file.c", "path/to", "file.c" },
		{ "/path/to/file.c", "/path/to", "file.c" },
	};



	plan(3 * TEST_CASES);

	for( int test_case = 0; test_case < TEST_CASES; test_case++ ) {
		/* 3 tests */
		path_test_spec cur_spec = fp_data[test_case];

		orion_filepath* fp_fwd_slash = orion_filepath_new_from_string(cur_spec.fp_path);
		is_string( cur_spec.fp_path,
			orion_filepath_to_string(fp_fwd_slash),
			"the path created from a path with forward slashes remains the same" );

		orion_filepath* fp_dir = orion_filepath_dir( fp_fwd_slash );
		/*[>DEBUG<]orion_filepath_dump( fp_dir );*/
		is_string( cur_spec.fp_dir,
			orion_filepath_to_string( fp_dir ), "(dir) removing the last component is correct");

		orion_filepath* fp_base = orion_filepath_base( fp_fwd_slash );
		/*[>DEBUG<]orion_filepath_dump( fp_base );*/
		is_string( cur_spec.fp_base,
			orion_filepath_to_string( fp_base ), "(base) the last component is correct");
	}



	return EXIT_SUCCESS;
}
