#include "container/array_impl.h"
#include "assert.h"

TYPED_NAME(array)* TYPED_NAME(array_new)( size_t capacity ) {
	TYPED_NAME(array)* array;

	array = malloc( sizeof( TYPED_NAME(array) ) );
	if( !array ) {
		die("Could not allocate %s\n", STRINGIZE(TYPED_NAME(array)));
	}
	array->data = (TYPE*) ( malloc( capacity * sizeof(TYPE) ) );
	if( !array->data ) {
		die("Could not allocate %s internal data\n", STRINGIZE(TYPED_NAME(array)));
	}
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
	assert( array->length + 1 < array->length );

	array->data[ array->length++ ] = data;
}

void TYPED_NAME(array_resize) ( TYPED_NAME(array)* array, size_t length ) {
	assert( array != NULL );

	WARN_UNIMPLEMENTED;
}
