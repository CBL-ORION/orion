#ifndef TYPE
    #error "missing declaration TYPE"
#endif
#ifndef TYPED_NAME
    #error "missing declaration TYPED_NAME"
#endif

#include "util/util.h"

/* TODO
 *
 * vector is fixed size
 */
typedef struct {
	size_t length;   /* number of items in the vector */
	TYPE * data;
} TYPED_NAME(vector);

/* ==== construct / destruct ==== */
extern TYPED_NAME(vector)* TYPED_NAME(vector_new)( size_t size );
extern void TYPED_NAME(vector_free)( TYPED_NAME(vector)* vector );

/* ==== getters ==== */
extern size_t TYPED_NAME(vector_length) ( TYPED_NAME(vector)* vector );


/* ==== element access ==== */
extern TYPE TYPED_NAME(vector_get) ( TYPED_NAME(vector)* vector, size_t index );
extern void TYPED_NAME(vector_set) ( TYPED_NAME(vector)* vector, size_t index, TYPE data );
