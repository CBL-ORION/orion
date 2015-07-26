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

TYPED_NAME(array) * TYPED_NAME(array_new) ( size_t size ) {
#define _T  TYPED_NAME(array)
	_T* arr = malloc( sizeof( _T ) );

	WARN_UNIMPLEMENTED;
	return NULL;
#undef _T
}

void TYPED_NAME(array_insert) ( TYPED_NAME(array) *array, TYPE data ) {
	WARN_UNIMPLEMENTED;
}
