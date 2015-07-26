#ifndef UTIL_H
#define UTIL_H 1

#include <stdlib.h>

#define SQUARED(x) ( (x) * (x) )

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)

#define SHOWORIGIN           __FILE__ "(" STRINGIZE(__LINE__) "): "

/* TODO test on MSVC? */
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

/*#define WARN_UNIMPLEMENTED DO_PRAGMA(message ("Warning: unimplemented")) */
#define WARN_UNIMPLEMENTED \
	 do { \
		fprintf(stderr, "%s Warning: unimplemented in %s\n", SHOWORIGIN, __FUNCTION__); \
		exit(EXIT_FAILURE); \
	} while(0)

#endif /* UTIL_H */
