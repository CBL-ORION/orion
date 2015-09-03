#ifndef UTIL_PREPROCESSOR_H
#define UTIL_PREPROCESSOR_H 1

/* stringifying macros */
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define TYPE_CAT(X,Y) PRIMITIVE_CAT(X, _ ## Y)

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)

/* error and todo macros */
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

#endif /* UTIL_PREPROCESSOR_H */
