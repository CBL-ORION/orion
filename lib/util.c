#include "util.h"

#include <string.h>

void die(const char* msg_fmt, ...) {
	va_list args;
	va_start(args, msg_fmt); \
	vfprintf(stderr, msg_fmt, args);
	va_end(args);
	exit(EXIT_FAILURE);
}

char* safe_malloc_and_strcpy(char* dest, char* src) {
	size_t len = strlen(src);
	NEW_COUNT(dest, char, len);
	return strncpy(dest, src, len);
}
