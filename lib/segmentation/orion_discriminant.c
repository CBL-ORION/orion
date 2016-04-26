#include "segmentation/orion_discriminant.h"

void orion_histogram_init(orion_discriminant_function* discrim, size_t m, size_t n) {
	discrim->m = m;
	discrim->n = n;

	NEW_COUNT(discrim->histogram, size_t, discrim->m * discrim->n);
	for( int hist_idx = 0; hist_idx < orion_histogram_elems(discrim); hist_idx++ ) {
		discrim->histogram[hist_idx] = 0;
	}
}
