#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "simple-log/simplelog.h"
#include "param/param.h"

void usage(char* program_name) {
	fprintf( stderr,
"%s [option]...\n\
    --scale _scale_ : _scale_ is a floating-point number.\n\
                      This option can be repeated multiple\n\
                      times to do multi-scale processing.\n\
\n\
    --input _path_   : _path_ is the filename for the input volume\n\
\n\
    --output _path_  : _path_ is the filename for the output volume\n\
    --help           : show this information\n\
",
		program_name
	);
}

void parse_arguments( int argc, char * argv[], orion_parameters* param ) {
	int arg_idx = 0;
	WARN_UNIMPLEMENTED;
	for( arg_idx = 0; arg_idx < argc; arg_idx++ ) {
		if( strcmp( argv[arg_idx], "--help" ) == 0 ) {
			usage( argv[0] );
			exit(EXIT_SUCCESS);
		} else if( strcmp( argv[arg_idx], "--scale" ) == 0 ) {
			if( (arg_idx+1) < argc )
				array_add_float( param->scales, atof( argv[arg_idx + 1] ) );
			else
				die("Missing argument to --scale");
		} else if( strcmp( argv[arg_idx], "--input" ) == 0 ) {
			WARN_UNIMPLEMENTED;
			safe_malloc_and_strcpy(param->input_filename, argv[arg_idx+1]);
		} else if(  strcmp( argv[arg_idx], "--output" ) == 0 ) {
			WARN_UNIMPLEMENTED;
			safe_malloc_and_strcpy(param->input_filename, argv[arg_idx+1]);
		}
	}

}

int main( int argc, char * argv[] ) {
	LOG_INFO("Starting %s", argv[0] );

	orion_parameters* param = orion_parameters_new();

	parse_arguments(argc, argv, param);

	LOG_INFO("Stopping %s", argv[0] );
	return EXIT_SUCCESS;
}
