#define TYPE int
#define TYPED_NAME(x) x ## _ ## int
#include "vector_impl.c"
#undef TYPE
#undef TYPED_NAME

#define TYPE float
#define TYPED_NAME(x) x ## _ ## float
#include "vector_impl.c"
#undef TYPE
#undef TYPED_NAME

#define TYPE char*
#define TYPED_NAME(x) x ## _ ## str
#include "vector_impl.c"
#undef TYPE
#undef TYPED_NAME

/* TODO: move to vector_impl.c */
void vector_dump_float(vector_float* vector) {
	size_t len = vector_length_float( vector );
	fprintf(stderr, "vector_float %p [\n", vector);
	for( size_t i = 0; i < len; i++ ) {
		fprintf(stderr, "\t%f", vector_get_float(vector, i));
	}
	fprintf(stderr, "\n]\n");
}
