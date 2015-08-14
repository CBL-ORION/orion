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
	fprintf(stderr, "[\n");
	for( int i = 0; i < len; i++ ) {
		fprintf(stderr, "\t%f", array_get_float(array, i));
	}
	fprintf(stderr, "[\n");
}
