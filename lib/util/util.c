#include "util/util.h"

#include <string.h>
#include <errno.h>

void _real_die(const char* msg_fmt, const char* origin, ...) {
	va_list args;
	va_start(args, origin); \
	fprintf(stderr, "%s ", origin);
	vfprintf(stderr, msg_fmt, args);
	if(errno) {
		/* TODO use strerror_r for thread-safe */
		fprintf(stderr, ": %s", strerror(errno));
		errno = 0; /* clear */
	}
	fprintf(stderr, "\n");
	va_end(args);
	exit(EXIT_FAILURE);
}

char* safe_malloc_and_strcpy(char** dest, const char* src) {
	size_t len = strlen(src);
	NEW_COUNT(*dest, char, len);
	return strncpy(*dest, src, len);
}

char* safe_malloc_and_strncpy(char** dest, const char* src, size_t len) {
	size_t src_len = strlen(src);
	if( len > src_len ) {
		die("Length requested for destination string is longer than the source string: %s > %s", len, src_len);
	}
	NEW_COUNT(*dest, char, len);
	return strncpy(*dest, src, len);
}
