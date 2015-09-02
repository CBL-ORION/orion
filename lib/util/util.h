#ifndef UTIL_UTIL_H
#define UTIL_UTIL_H 1

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "util/float.h"
#include "util/string.h"

#define SQUARED(x) ( (x) * (x) )

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define TYPE_CAT(X,Y) PRIMITIVE_CAT(X, _ ## Y)

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)

#define SHOWORIGIN           __FILE__ ":" STRINGIZE(__LINE__) ":0:"

/* TODO test on MSVC? */
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#ifdef COMPILE_WARN_UNIMPLEMENTED
#   define WARN_UNIMPLEMENTED DO_PRAGMA(message ("Warning: unimplemented"))
#else
#   define WARN_UNIMPLEMENTED \
	 do { \
		fprintf(stderr, "%s Warning: unimplemented in %s\n", SHOWORIGIN, __FUNCTION__); \
		exit(EXIT_FAILURE); \
	} while(0)
#endif /* COMPILE_WARN_UNIMPLEMENTED */


extern void _real_die(const char* msg_fmt, const char* origin, ...);
#define die(_msg_fmt, ...) _real_die(_msg_fmt, SHOWORIGIN, __VA_ARGS__)

#define NEW_COUNT(_var, _type, _count) \
	do { \
		if( !( (_var) = (_type*)malloc( (_count) * sizeof(_type) ) ) ) \
			die("%s Error: Could not allocate memory: [type: %s, count: %d]", SHOWORIGIN, STRINGIZE(_type), (_count)); \
	} while(0)
#define NEW(_var, _type) NEW_COUNT(_var, _type, 1)

#define RESIZE_COUNT(_var, _type, _count) \
	do { \
		if( !( (_var) = (_type*)realloc((_var), (_count) * sizeof(_type) ) ) ) \
			die("%s Error: Could not reallocate memory: [type: %s, count: %d]", SHOWORIGIN, STRINGIZE(_type), (_count)); \
	} while(0)

#endif /* UTIL_UTIL_H */
