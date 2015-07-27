#include "container/array_impl.h"
#include "assert.h"

#ifndef ARRAY_IMPL_RESIZE_FACTOR_GUARD
#define ARRAY_IMPL_RESIZE_FACTOR_GUARD
const size_t ARRAY_IMPL_RESIZE_FACTOR = 2;
#endif /* ARRAY_IMPL_RESIZE_FACTOR_GUARD */

TYPED_NAME(array)* TYPED_NAME(array_new)( size_t capacity ) {
	TYPED_NAME(array)* array;

	NEW(array, TYPED_NAME(array));
	NEW_COUNT(array->data, TYPE, capacity);

	array->capacity = capacity;
	array->length = 0;

	return array;
}

void TYPED_NAME(array_free)( TYPED_NAME(array)* array ) {
	assert( array != NULL );

	free( array->data );
	free( array );
}

/* accessor for capacity */
size_t TYPED_NAME(array_capacity) ( TYPED_NAME(array)* array ) {
	assert( array != NULL );
	return array->capacity;
}

/* accessor for length */
size_t TYPED_NAME(array_length) ( TYPED_NAME(array)* array ) {
	assert( array != NULL );
	return array->length;
}

TYPE TYPED_NAME(array_get) ( TYPED_NAME(array)* array, size_t index ) {
	assert( array != NULL );
	assert( index < array->length );

	return array->data[index];
}

void TYPED_NAME(array_set) ( TYPED_NAME(array)* array, size_t index, TYPE data ) {
	assert( array != NULL );
	assert( index < array->length );

	array->data[index] = data;
}

void TYPED_NAME(array_add) ( TYPED_NAME(array)* array, TYPE data ) {
	assert( array != NULL );
	if(  array->length + 1 > array->capacity ) {
		TYPED_NAME(array_resize)(array, array->capacity * ARRAY_IMPL_RESIZE_FACTOR);
	}

	array->data[ array->length++ ] = data;
}

void TYPED_NAME(array_resize) ( TYPED_NAME(array)* array, size_t new_capacity ) {
	assert( array != NULL );
	RESIZE_COUNT(array->data, TYPE, new_capacity);
	array->capacity = new_capacity;
}
