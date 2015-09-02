#include <string.h>

#include "util/util.h"
#include "util/string.h"

char* safe_malloc_and_strcpy(char** dest, const char* src) {
	/* add 1 so that there is room for the null-terminator and so that
	 * `strncpy` will also copy the null-terminator */
	size_t len = strlen(src) + 1;
	NEW_COUNT(*dest, char, len);
	strncpy(*dest, src, len);
	return *dest;
}

char* safe_malloc_and_strncpy(char** dest, const char* src, size_t len) {
	/* length of the buffer is one more than the length of the string
	 * copied so that there is room for the null-terminator */
	size_t buf_len = len + 1;

	/* check the size being copied versus the size of the source string */
	size_t src_len = strlen(src);
	if( len > src_len ) {
		die("Length requested for destination string is longer than the source string: %s > %s", len, src_len);
	}

	/* allocate space and copy the string buffer */
	NEW_COUNT(*dest, char, buf_len);
	strncpy(*dest, src, len);

	/* make sure that the string is null-terminated */
	(*dest)[buf_len - 1] = '\0';

	return *dest;
}
