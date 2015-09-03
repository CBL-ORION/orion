#include <stdlib.h>
#include <string.h>
#include <tap/basic.h>

#include "io/path/path.h"

int main(void) {
	/* data */
	typedef struct {
		/* input */
		char* fp_path_input;

		/* expected output */
		char* fp_path;
		char* fp_dir;
		char* fp_base;
	} path_test_spec;

	path_test_spec fp_data[] = {
		/* fp_path_input     ,   fp_path        ,   fp_dir  ,  fp_base  */
		{ "path/to/file.c"   ,  "path/to/file.c",  "path/to", "file.c" },
		{ "/path/to/file.c"  , "/path/to/file.c", "/path/to", "file.c" },
		{ "path\\to\\file.c" ,  "path/to/file.c",  "path/to", "file.c" },
		{ "\\path/to\\file.c", "/path/to/file.c", "/path/to", "file.c" },
	};
	const size_t TEST_CASES = sizeof( fp_data ) / sizeof( path_test_spec );



	plan(3 * TEST_CASES);

	for( size_t test_case = 0; test_case < TEST_CASES; test_case++ ) {
		/* 3 tests */
		path_test_spec cur_spec = fp_data[test_case];

		orion_filepath* fp = orion_filepath_new_from_string(cur_spec.fp_path_input);
		is_string( cur_spec.fp_path,
			orion_filepath_to_string(fp),
			"expected normalised path is correct" );

		orion_filepath* fp_dir = orion_filepath_dir( fp );
		/*[>DEBUG<]orion_filepath_dump( fp_dir );*/
		is_string( cur_spec.fp_dir,
			orion_filepath_to_string( fp_dir ),
			"(dir) removing the last component is correct");

		orion_filepath* fp_base = orion_filepath_base( fp );
		/*[>DEBUG<]orion_filepath_dump( fp_base );*/
		is_string( cur_spec.fp_base,
			orion_filepath_to_string( fp_base ),
			"(base) the last component is correct");
	}



	return EXIT_SUCCESS;
}
