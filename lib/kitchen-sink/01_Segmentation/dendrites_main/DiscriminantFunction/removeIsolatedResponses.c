#include "kitchen-sink/01_Segmentation/dendrites_main/DiscriminantFunction/removeIsolatedResponses.h"
/* TODO
 *
 * Refactor: removeIsolatedResponses
 */

#include "numeric/sample.h"
#include <float.h>
#include "simple-log/simplelog.h"

/* orion_removeIsolatedResponses
 *
 * Identify the indices of features that are non-isolated so that only features
 * that are representative of a cluster are examined as part of the histogram.
 */
void orion_removeIsolatedResponses(
		orion_segmentation_param* param,
		orion_features*  features,
		orion_discriminant_function* discrim,
		array_int* sample_instance_indices,
		array_int** non_isolated_instance_indices
		) {

	pixel_type* min_bound;
	pixel_type* max_bound;

	NEW_COUNT( min_bound, pixel_type, features->number_of_features );
	NEW_COUNT( max_bound, pixel_type, features->number_of_features );

	size_t sample_instance_indices_size = array_length_int( sample_instance_indices );

	uint32_t iterations = 200;
	size_t samples_in_each_round = 200;
	if( samples_in_each_round > sample_instance_indices_size ) {
		samples_in_each_round = sample_instance_indices_size;
	}

	*non_isolated_instance_indices = array_new_int( sample_instance_indices_size );


	for( int feat_idx = 0; feat_idx < features->number_of_features; feat_idx++ ) {
		/* init bounds to zero */
		min_bound[feat_idx] = 0;
		max_bound[feat_idx] = 0;

		/* sample each feature independently */
		for( uint32_t sample_round = 0; sample_round < iterations ; sample_round++ ) {
			array_int* sample = array_random_sample_int(
					param->rng_state,
					samples_in_each_round,
					sample_instance_indices_size );

			pixel_type min_for_round = FLT_MAX, max_for_round = -FLT_MAX;
			for( int sample_idx = 0; sample_idx < samples_in_each_round; sample_idx++ ) {
				size_t sample_instance_idx = array_get_int( sample, sample_idx );
				size_t instance_idx = array_get_int( sample_instance_indices, sample_instance_idx );

				pixel_type cur_feature = vector_get_float(
							features->features[feat_idx],
							instance_idx
						);

				if( min_for_round > cur_feature ) { min_for_round = cur_feature; }
				if( max_for_round < cur_feature ) { max_for_round = cur_feature; }
			}

			/* divide by iterations because we want the average of all the
			 * rounds */
			min_bound[feat_idx] += min_for_round / iterations;
			max_bound[feat_idx] += max_for_round / iterations;

			array_free_int( sample );
			/*[>DEBUG<]LOG_DEBUG( "feat: %d ; min: %e ; max: %e",
					feat_idx,
					min_bound[feat_idx],
					max_bound[feat_idx]);*/
		}

		pixel_type interval_size = max_bound[feat_idx] - min_bound[feat_idx];
		pixel_type mean = (max_bound[feat_idx] - min_bound[feat_idx]) / 2.0;

		/* re-assign to min and max bounds by creating region that is
		 * three times the interval size */
		min_bound[feat_idx] = mean - 2 * interval_size;
		max_bound[feat_idx] = mean + 2 * interval_size;
		/*[>DEBUG<]LOG_DEBUG( "feat: %d ; min: %e ; max: %e",
				feat_idx,
				min_bound[feat_idx],
				max_bound[feat_idx]);*/
	}

	/* only keep values that are within both bounds */
	for( int i = 0; i < sample_instance_indices_size; i++ ) {
		size_t current_sample_idx = array_get_int( sample_instance_indices, i );
		/* check if the feature is in the bounds for all features */
		bool in_bounds = true;
		for( int feat_idx = 0; in_bounds && feat_idx < features->number_of_features; feat_idx++ ) {
			pixel_type cur_feature = vector_get_float(
						features->features[feat_idx],
						current_sample_idx
					);
			/*[>DEBUG<]LOG_DEBUG("cur feature: %f", cur_feature);*/
			in_bounds &= cur_feature >= min_bound[feat_idx]
				&&   cur_feature <= max_bound[feat_idx];
		}
		if( in_bounds ) {
			array_add_int( *non_isolated_instance_indices, current_sample_idx );
		}
	}


	free( min_bound );
	free( max_bound );
}
