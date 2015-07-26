#include "util.h"

void die(const char* msg_fmt, ...) {
	va_list args;
	va_start(args, msg_fmt); \
	vfprintf(stderr, msg_fmt, args);
	va_end(args);
	exit(EXIT_FAILURE);
}

void safe_malloc_and_strcpy(char* dest, char* src) {
	/* strlen()
	 * if( malloc ) perror()
	 * strncpy()
	 */
	WARN_UNIMPLEMENTED;
}
