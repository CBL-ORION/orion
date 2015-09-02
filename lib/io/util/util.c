#include "io/util/util.h"
#include "array/array.h"

int orion_freadline(FILE* fh, char* buffer) {
	return fscanf(fh, "%[^\r\n]\n", buffer);
}

array_int* orion_parse_sequence_int(const char* buffer) {
	TODO()
}

array_int* orion_parse_sequence_float(const char* buffer) {
	TODO()
}
