#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "simple-log/simplelog.h"
#include "param/param.h"
#include "util/util.h"
#include "util/util.h"
#include "io/path/path.h"
#include "io/format/mhd.h"

#include "kitchen-sink/01_Segmentation/dendrites_main/ORION3_Dendrites.h"

#include "orion3-config-parser/parser.h"

#define ORION_METAINFO_FILE_FMT_SUFFIX ".mhd"

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
\n\
    --orion3-config _path_  : _path_ is the filename for the ORION3 configuration file\n\
\n\
    --help           : show this information\n\
",
		program_name
	);
}

void parse_arguments( int argc, char * argv[], param_parse* param ) {
	int arg_idx = 0;
	if( argc == 1 ) {
		usage( argv[0] );
		exit(EXIT_SUCCESS);
	}
	for( arg_idx = 1; arg_idx < argc; arg_idx++ ) {
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
		} else if(  strcmp( argv[arg_idx], "--orion3-config" ) == 0 ) {
			if( arg_idx+1 < argc )
				safe_malloc_and_strcpy(&(param->io->orion3_config_filename), argv[arg_idx+1]);
			else
				die("Missing argument to --orion3-config at %d", arg_idx + 1);
		}
	}

}

void parse_param_dump(param_parse* param) {
	orion_io_param_dump(param->io);
	orion_segmentation_param_dump(param->segmentation);
}

void orion3_config_set_parameters(param_parse* param) {
	orion3_param* config_param =
		orion3_param_read_input_file( param->io->orion3_config_filename );

	/* copy the scales from the configuration */
	for( size_t scale_idx = 0; scale_idx < array_length_float(config_param->scales); scale_idx++ ) {
		array_add_float( param->segmentation->scales,
				array_get_float( config_param->scales, scale_idx ) );
	}

	/* copy the input volume from the configuration */
	size_t n_volumes = array_length_str(config_param->volume_names);
	if( n_volumes > 0 ) {
		if( n_volumes == 1 ) {
			/*
			 * final path is:
			 *
			 * < path-to-volume-directory > / < volume-name > / < volume-name >.mhd
			 */
			orion_filepath* fp_base_dir = orion_filepath_new_from_string(config_param->path_to_volume_directory);

			char* vol_name = array_get_str( config_param->volume_names, 0 );
			size_t vol_name_len = strlen(vol_name);

			char* vol_name_suffix;
			NEW_COUNT(vol_name_suffix, char, vol_name_len + strlen(ORION_METAINFO_FILE_FMT_SUFFIX) + 1 );

			strncpy(vol_name_suffix, vol_name, vol_name_len),

			/* add MetaInfo suffix */
			strncpy(vol_name_suffix + vol_name_len,
					ORION_METAINFO_FILE_FMT_SUFFIX,
					strlen(ORION_METAINFO_FILE_FMT_SUFFIX) + 1);

			orion_filepath* fp_vol_dir = orion_filepath_new_from_string( vol_name );
			orion_filepath* fp_vol_filename = orion_filepath_new_from_string( vol_name_suffix );

			orion_filepath* fp_vol_dir_file = orion_filepath_cat( fp_vol_dir, fp_vol_filename );

			orion_filepath* fp_vol_full_path = orion_filepath_cat( fp_base_dir, fp_vol_dir_file );

			safe_malloc_and_strcpy(&(param->io->input_filename),
				orion_filepath_to_string(fp_vol_full_path) );

			free(vol_name_suffix);
			orion_filepath_free(fp_vol_full_path);
			orion_filepath_free(fp_vol_dir_file);
			orion_filepath_free(fp_vol_filename);
			orion_filepath_free(fp_base_dir);
		} else {
			die("Can not handle multiple volumes in configuration %s",
					param->io->orion3_config_filename);
		}
	} else {
		die("No volumes files given in configuration %s",
				param->io->orion3_config_filename);
	}

	orion3_param_free( config_param );
}

int main( int argc, char * argv[] ) {
	LOG_INFO("Starting %s", argv[0] );

	param_parse* param;
	NEW( param, param_parse );
	param->io = orion_io_param_new();
	param->segmentation = orion_segmentation_param_new();

	parse_arguments(argc, argv, param);

	/* read in parameters from configuration file */
	if( param->io->orion3_config_filename ) {
		orion3_config_set_parameters(param);
	}

	/*DEBUG*/parse_param_dump(param);

	ndarray3* input_volume = orion_read_mhd( param->io->input_filename );

	orion_ORION3_Dendrites( param->segmentation, input_volume );

	ndarray3_free(input_volume);
	orion_io_param_free(param->io);
	orion_segmentation_param_free( param->segmentation );
	LOG_INFO("Stopping %s", argv[0] );
	return EXIT_SUCCESS;
}
