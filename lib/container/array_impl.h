#ifndef TYPE
    #error "missing declaration TYPE"
#endif
#ifndef TYPED_NAME
    #error "missing declaration TYPED_NAME"
#endif

#include "util.h"

typedef struct {
	size_t length;
	size_t size;
	TYPE *data;
} TYPED_NAME(array);

#define _T  TYPED_NAME(array) /* shorten type */

_T* TYPED_NAME(array_new)( size_t size ) {

	_T* arr = malloc( sizeof( _T ) );

	WARN_UNIMPLEMENTED;
	return NULL;
}

void TYPED_NAME(array_insert) ( _T* array, TYPE data ) {
	WARN_UNIMPLEMENTED;
}

#undef _T
