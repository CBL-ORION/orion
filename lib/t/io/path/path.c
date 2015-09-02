#include <stdlib.h>
#include <string.h>
#include <tap/basic.h>

#include "io/path/path.h"

int main(void) {
	plan(1 + 1 + 1);

	/* data */
	char* fp_str_fwd_slash = "path/to/file.c";

/* 1 test */
	orion_filepath* fp_fwd_slash = orion_filepath_new_from_string(fp_str_fwd_slash);
	is_string( fp_str_fwd_slash,
		orion_filepath_to_string(fp_fwd_slash),
		"the path created from a path with forward slashes remains the same" );

/* 1 test */
	orion_filepath* fp_dir = orion_filepath_dir( fp_fwd_slash );
	/*[>DEBUG<]orion_filepath_dump( fp_dir );*/
	is_string( "path/to",
		orion_filepath_to_string( fp_dir ), "(dir) removing the last component is correct");

/* 1 test */
	orion_filepath* fp_base = orion_filepath_base( fp_fwd_slash );
	/*[>DEBUG<]orion_filepath_dump( fp_base );*/
	is_string( "file.c",
		orion_filepath_to_string( fp_base ), "(base) the last component is correct");


	return EXIT_SUCCESS;
}
