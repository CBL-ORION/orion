#define TYPE int
#define TYPED_NAME(x) x ## _ ## int
#include "array_impl.c"
#undef TYPE
#undef TYPED_NAME

#define TYPE float
#define TYPED_NAME(x) x ## _ ## float
#include "array_impl.c"
#undef TYPE
#undef TYPED_NAME

#define TYPE char*
#define TYPED_NAME(x) x ## _ ## str
#include "array_impl.c"
#undef TYPE
#undef TYPED_NAME

/* TODO: move to array_impl.c */
void array_dump_float(array_float* array) {
	size_t len = array_length_float( array );
	fprintf(stderr, "array_float %p [\n", array);
	for( size_t i = 0; i < len; i++ ) {
		fprintf(stderr, "\t%f", array_get_float(array, i));
	}
	fprintf(stderr, "\n]\n");
}

void array_dump_str(array_str* array) {
	size_t len = array_length_str( array );
	fprintf(stderr, "array_str %p [\n", array);
	for( size_t i = 0; i < len; i++ ) {
		fprintf(stderr, "\t%s\n", array_get_str(array, i));
	}
	fprintf(stderr, "]\n");
}
