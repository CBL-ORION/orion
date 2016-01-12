#include "container/vector_impl.h"
#include <assert.h>
#include <stdio.h>

TYPED_NAME(vector)* TYPED_NAME(vector_new)( size_t length ) {
	TYPED_NAME(vector)* vector;

	NEW(vector, TYPED_NAME(vector));
	NEW_COUNT(vector->data, TYPE, length);

	vector->length = length;

	return vector;
}

void TYPED_NAME(vector_free)( TYPED_NAME(vector)* vector ) {
	assert( vector != NULL );

	free( vector->data );
	free( vector );
}

/* accessor for length */
size_t TYPED_NAME(vector_length) ( TYPED_NAME(vector)* vector ) {
	assert( vector != NULL );
	return vector->length;
}

TYPE TYPED_NAME(vector_get) ( TYPED_NAME(vector)* vector, size_t index ) {
	assert( vector != NULL );
	assert( index < vector->length );

	return vector->data[index];
}

void TYPED_NAME(vector_set) ( TYPED_NAME(vector)* vector, size_t index, TYPE data ) {
	assert( vector != NULL );
	assert( index < vector->length );

	vector->data[index] = data;
}
