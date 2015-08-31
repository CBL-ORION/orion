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

char* safe_malloc_and_strcpy(char** dest, char* src) {
	size_t len = strlen(src);
	NEW_COUNT(*dest, char, len);
	return strncpy(*dest, src, len);
}
