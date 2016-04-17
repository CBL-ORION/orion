#include "numeric/sample.h"

#include <assert.h>

/* Returns an array_int of length `sample_size`
 * where each element is
 *
 * - in the range 0 to `population_size` - 1 and
 * - sampled randomly without replacement.
 *
 * See Algorithm 3.4.2S of Knuth's book Seminumeric Algorithms: "Selection
 * Sampling Technique".
 */
array_int* array_random_sample_int(
		orion_rand_state_t* rng_state,
		uint32_t sample_size,
		uint32_t population_size) {
	/* we can not sample more things than actually exist */
	assert( sample_size <= population_size );

	array_int* samples = array_new_int( sample_size );

	/* To select $ n $ records at random from a set of $ N $, where
	 * $ 0 < n ≤ N $ .  */
	uint32_t n = sample_size;
	uint32_t N = population_size;

	/* S1. [Initialise.]
	 *********************
	 * - m: number of records selected so far
	 * - t: total number of input records we have dealt with */
	uint32_t m = 0;
	uint32_t t = 0;

	while( m < n ) {
		/* S2. [Generate $ U $.]
		 *************************
		 * Generate a random number $ U $, from a uniform distribution
		 * $ uniform(0, 1) $.  */
		float32 U = orion_rand_uniform_dist(rng_state);
		/* S3. [Test.]
		 ***************
		 * If $ (N - t) U ≥ n - m $, go to step S5. */
		if( (N - t) * U >= n - m ) {
			/* S5. [Skip.]
			 ***************
			 * Skip the next record (do not include it in the
			 * sample), increase t by 1, and go to step S2.  */
			t++;
			continue;
		} else {
			/* S4. [Select.]
			 *****************
			 * Select the next record for the sample, and increase
			 * m and t by 1.  If m < n, go to step S2; otherwise
			 * the sample is complete and the algorithm terminates.  */
			array_add_int( samples, t ); /* set m-th element to t */
			m++;
			t++;
		}

	}

	return samples;
}
