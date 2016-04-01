#include "segmentation/orion_features.h"

orion_features* orion_features_new( size_t instances ) {
	orion_features* f;
	NEW( f, orion_features );
	f->number_of_features = ORION_NUMBER_OF_SEGMENTATION_FEATURES;
	f->number_of_instances = instances;
	for( size_t f_idx = 0; f_idx < f->number_of_features; f_idx++ ) {
		f->features[f_idx] = vector_new_float( instances );
	}

	return f;
}

void orion_features_free( orion_features* f ) {
	for( size_t f_idx = 0; f_idx < f->number_of_features; f_idx++ ) {
		vector_free_float( f->features[f_idx] );
		f->features[f_idx] = NULL;
	}
}
