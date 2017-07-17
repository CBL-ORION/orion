#include <tap/basic.h>
#include <tap/float.h>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "numeric/random.h"
#include "util/util.h"

int main(int argc, char** argv) {
	plan(2);


	kiss99_rng_state* state = kiss99_rng_state_new();
	kiss99_rng_init( state );

	const size_t number_of_samples = 1E7;
	/* theoretical mean and variance of
	 * uniform distribution U(0,1) */
	const float64 uniform_dist_mean = 0.5;
	const float64 uniform_dist_var = 1.0/12.0;

	float64 sum = 0.0;
	float64 sum_of_sq = 0.0;
	for( int i = 0; i < number_of_samples; i++ ) {
		float64 sample = orion_rand_uniform_dist( state );

		sum += sample;
		sum_of_sq += SQUARED( sample - uniform_dist_mean );
	}

	float64 mean = sum / number_of_samples;
	float64 var = sum_of_sq / number_of_samples;

	/* 2 tests */
	is_double( uniform_dist_mean, mean, 1E-3, "Mean of U(0,1) = 1/2" );
	is_double( uniform_dist_var, var, 1E-3, "Variance of U(0,1) = 1/12" );

	return EXIT_SUCCESS;
}
