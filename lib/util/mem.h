#ifndef UTIL_MEM_H
#define UTIL_MEM_H 1

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

#endif /* UTIL_MEM_H */
