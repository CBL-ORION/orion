#include <stddef.h>

#include "util/util.h"

typedef struct {
	char** components;
	size_t number_of_components;
} orion_filepath;

orion_filepath* orion_filepath_new_from_string() {
	TODO( normalise the backslashes to forward slashes on Windows );
	TODO( split into components );
	WARN_UNIMPLEMENTED;
}

char* orion_filepath_basename() {
	TODO( copy last component );
}

char* orion_filepath_dirname() {
	TODO( copy last component );
}

void orion_filepath_free( orion_filepath* fp ) {
	TODO( free );
}

char* orion_filepath_to_string(orion_filepath*) {
	TODO( strcat );
}

