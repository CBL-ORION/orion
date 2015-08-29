#ifndef TYPE
    #error "missing declaration TYPE"
#endif
#ifndef TYPED_NAME
    #error "missing declaration TYPED_NAME"
#endif

#include "util/util.h"

typedef struct {
	size_t capacity; /* maximum size */
	size_t length;   /* number of items in the array */
	TYPE * data;
} TYPED_NAME(array);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ==== construct / destruct ==== */
extern TYPED_NAME(array)* TYPED_NAME(array_new)( size_t size );
extern void TYPED_NAME(array_free)( TYPED_NAME(array)* array );

/* ==== getters ==== */
extern size_t TYPED_NAME(array_capacity) ( TYPED_NAME(array)* array );
extern size_t TYPED_NAME(array_length) ( TYPED_NAME(array)* array );


/* ==== element access ==== */
extern TYPE TYPED_NAME(array_get) ( TYPED_NAME(array)* array, size_t index );
extern void TYPED_NAME(array_set) ( TYPED_NAME(array)* array, size_t index, TYPE data );
extern void TYPED_NAME(array_add) ( TYPED_NAME(array)* array, TYPE data );

/* ==== memory management ==== */
extern void TYPED_NAME(array_resize) ( TYPED_NAME(array)* array, size_t new_capacity );

#ifdef __cplusplus
};
#endif /* __cplusplus */
