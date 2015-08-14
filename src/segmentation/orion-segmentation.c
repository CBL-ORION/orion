#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "simple-log/simplelog.h"
#include "param/param.h"
#include "util.h"

typedef struct {
	orion_io_param* io;
	orion_segmentation_param* segmentation;
} param_parse;

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

void parse_arguments( int argc, char * argv[], param_parse* param ) {
	int arg_idx = 0;
	for( arg_idx = 0; arg_idx < argc; arg_idx++ ) {
		if( strcmp( argv[arg_idx], "--help" ) == 0 ) {
			usage( argv[0] );
			exit(EXIT_SUCCESS);
		} else if( strcmp( argv[arg_idx], "--scale" ) == 0 ) {
			if( arg_idx+1 < argc )
				array_add_float( param->segmentation->scales, atof( argv[arg_idx + 1] ) );
			else
				die("Missing argument to --scale at %d", arg_idx+1);
		} else if( strcmp( argv[arg_idx], "--input" ) == 0 ) {
			if( arg_idx+1 < argc )
				safe_malloc_and_strcpy(&(param->io->input_filename), argv[arg_idx+1]);
			else
				die("Missing argument to --input at %d", arg_idx+1);
		} else if(  strcmp( argv[arg_idx], "--output" ) == 0 ) {
			if( arg_idx+1 < argc )
				safe_malloc_and_strcpy(&(param->io->output_filename), argv[arg_idx+1]);
			else
				die("Missing argument to --output at %d", arg_idx + 1);
		}
	}

}

int main( int argc, char * argv[] ) {
	LOG_INFO("Starting %s", argv[0] );

	param_parse* param;
	NEW( param, param_parse );
	param->io = orion_io_param_new();
	param->segmentation = orion_segmentation_param_new();

	parse_arguments(argc, argv, param);

	orion_io_param_dump(param->io);
	orion_segmentation_param_dump(param->segmentation);

	LOG_INFO("Stopping %s", argv[0] );
	return EXIT_SUCCESS;
}
