#include "segmentation/orion_discriminant.h"

void orion_histogram_init(orion_discriminant_function* discrim, size_t m, size_t n) {
	discrim->bin_sz[0] = m;
	discrim->bin_sz[1] = n;

	NEW_COUNT(discrim->histogram, size_t, discrim->bin_sz[0] * discrim->bin_sz[1]);
	NEW_COUNT(discrim->norm_histogram, pixel_type, discrim->bin_sz[0] * discrim->bin_sz[1]);
	for( int hist_idx = 0; hist_idx < orion_histogram_elems(discrim); hist_idx++ ) {
		discrim->histogram[hist_idx] = 0;
		discrim->norm_histogram[hist_idx] = 0.0;
	}
}
