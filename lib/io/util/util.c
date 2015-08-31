#include "io/util/util.h"

int orion_freadline(FILE* fh, char* buffer) {
	return fscanf(fh, "%[^\n]\n", buffer);
}
