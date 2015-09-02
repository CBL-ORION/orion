#include <stddef.h>
#include <string.h>

#include "util/util.h"
#include "io/path/path.h"

orion_filepath* orion_filepath_new_from_string(const char* fp_string) {
	TODO( normalise the backslashes to forward slashes on Windows );
	char* fp_norm;
	size_t fp_len;
	safe_malloc_and_strcpy(&fp_norm, fp_string);
	fp_len = strlen( fp_string );


	TODO( split into components );
	WARN_UNIMPLEMENTED;
}

char* orion_filepath_base( orion_filepath* fp ) {
	TODO( copy last component );
}

char* orion_filepath_dir( orion_filepath* fp ) {
	TODO( copy last component );
}

void orion_filepath_free(orion_filepath* fp) {
	TODO( free );
}

char* orion_filepath_to_string(orion_filepath* fp) {
	TODO( strcat );
	return NULL;
}

