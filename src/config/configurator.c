#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Inspired by CCAN configurator:
 *
 * See <https://github.com/rustyrussell/ccan/blob/master/tools/configurator/configurator.c>.
 */

#define COMMAND_LINE_BUFFER_LENGTH 16384 /* pow(2,14) */

/* the extension used for executables */
#ifndef PLATFORM_EXE_EXT
#define PLATFORM_EXE_EXT ""
#endif /* PLATFORM_EXE_EXT */

#define DEFAULT_CC "cc"
#define DEFAULT_CFLAGS "-g3 -ggdb -Wall -Wundef -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wold-style-definition"

#ifndef CONFIG_HEADER_FILENAME
#define CONFIG_HEADER_FILENAME "config.h"
#endif /* CONFIG_HEADER_FILENAME */

#define CONFIG_HEADER_START \
	"#ifndef CONFIG_H\n" \
	"#define CONFIG_H 1\n\n" \

#define CONFIG_HEADER_END \
	"\n\n" \
	"#endif /* CONFIG_H */\n"

typedef enum {
	WHOLE_PROGRAM,
	INSIDE_MAIN
} test_code_type;

typedef enum {
	CHECK_COMPILE_ONLY,
	CHECK_EXECUTE
} test_check_type;

typedef struct {
	const char* define_name;
	const test_code_type   code_type;
	const test_check_type check_type;
	const char* cflags;
	const char* ldflags;
	const char* include_headers;
	const char* code_before_main;
	const char* code;

	/* results: false by default */
	bool test_done;
	bool define_value;
} config_test;

#define MAIN_TEMPLATE_START "int main(int argc, char** argv) {\n"
#define MAIN_TEMPLATE_BODY  "return 0;\n"
#define MAIN_TEMPLATE_END   "}\n"

config_test config_test_gen[] = {
	{
		"HAVE_BUILTIN_EXPECT",
		INSIDE_MAIN,
		CHECK_COMPILE_ONLY,
		NULL, NULL, NULL, NULL,

		"return __builtin_expect(argc == 1, 1) ? 0 : 1;\n"
	},
};

int compile( const char* src_filename, const char* bin_filename, config_test* test ) {
	char cmd_buffer[COMMAND_LINE_BUFFER_LENGTH];
	sprintf( cmd_buffer,
			"%s %s %s %s %s -o %s",
			/*1  2  3  4  5     6 */
			DEFAULT_CC,                         /* 1 */
			DEFAULT_CFLAGS,                     /* 2 */
			test->cflags ? test->cflags : "",   /* 3 */
			test->ldflags ? test->ldflags : "", /* 4 */
			src_filename,                       /* 5 */
			bin_filename                        /* 6 */
		);
	fprintf(stderr, "==> %s\n", cmd_buffer); /* TODO if verbose */
	int compile_ret = system(cmd_buffer);
	return compile_ret;
}

void output_test(FILE* fh, config_test* test) {
	if( test->include_headers ) {
		fprintf(fh, test->include_headers);
	}
	if( test->code_before_main ) {
		fprintf(fh, test->code_before_main);
	}
	fprintf(fh, MAIN_TEMPLATE_START);
	fprintf(fh, "%s",
			test->code
			? test->code
			: MAIN_TEMPLATE_BODY );
	fprintf(fh, MAIN_TEMPLATE_END);
}

int main( int argc, char** argv ) {
	size_t n_of_tests = sizeof( config_test_gen ) / sizeof( config_test );

	for(int test_idx = 0 ; test_idx < n_of_tests; test_idx++ ) {
		config_test* cur_test = &config_test_gen[test_idx];
		const char* src_filename = "test.c";
		const char* bin_filename = "test" PLATFORM_EXE_EXT;

		FILE* src_fh = fopen(src_filename, "w");

		if( !src_fh ) {
			return EXIT_FAILURE;
		}

		output_test( src_fh, cur_test );

		fclose(src_fh);

		int compile_ret = compile( src_filename, bin_filename, cur_test );

		cur_test->test_done = 1;

		/* booleanify `compile_ret`:
		 *
		 * If compile failed, then compile_ret > 0.
		 *
		 *   ! compile_ret => 0
		 *
		 * If compile is successful, the compile_ret == 0.
		 *
		 *   ! compile_ret => 1
		 *
		 */

		cur_test->define_value = !compile_ret;

		/* clean up */
		remove( src_filename );
		remove( bin_filename );
	}

	FILE* config_h_fh = stdout;
		/*= fopen(CONFIG_HEADER_FILENAME, "w");*/
	fprintf(config_h_fh, CONFIG_HEADER_START);
	for(int test_idx = 0 ; test_idx < n_of_tests; test_idx++ ) {
		config_test* cur_test = &config_test_gen[test_idx];
		if( cur_test->test_done ) {
			fprintf(config_h_fh, "#define %s %d\n",
					cur_test->define_name,
					0 + cur_test->define_value);
		}
	}
	fprintf(config_h_fh, CONFIG_HEADER_END);
	/*fclose( config_h_fh );*/

	return EXIT_SUCCESS;
}
