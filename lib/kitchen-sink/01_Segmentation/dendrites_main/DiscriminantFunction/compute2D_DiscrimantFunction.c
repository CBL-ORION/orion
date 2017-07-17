#include "kitchen-sink/01_Segmentation/dendrites_main/DiscriminantFunction/compute2D_DiscrimantFunction.h"

#include "kitchen-sink/01_Segmentation/dendrites_main/DiscriminantFunction/removeIsolatedResponses.h"

#define MAX_NUMBER_OF_HISTOGRAM_SAMPLES 1E6

#include "numeric/sample.h"
#include "vis/vis.hxx"

#include <math.h>
#include <float.h>
#include <assert.h>

/* Private prototypes */
void orion_hist3(
		orion_segmentation_param* param,
		orion_features* features,
		array_int* indices,
		orion_discriminant_function* discrim
		);

void orion_normaliseHistogram(
		orion_segmentation_param* param,
		orion_discriminant_function* discrim
		);

/* MATLAB version: compute2D_DiscrimantFunction */

/* TODO document */
void orion_compute2D_DiscrimantFunction(
		orion_segmentation_param* param,
		orion_features* features,
		array_int* instance_indices,
		orion_discriminant_function* discrim
		) {

	size_t n_samples = array_length_int( instance_indices );
	array_int* sample_instance_indices;
	array_int* non_isolated_instance_indices;

	if( n_samples > MAX_NUMBER_OF_HISTOGRAM_SAMPLES ) {
		/* only process at most MAX_NUMBER_OF_HISTOGRAM_SAMPLES features */
		sample_instance_indices =
			array_random_sample_int(param->rng_state, n_samples, MAX_NUMBER_OF_HISTOGRAM_SAMPLES);
		n_samples = MAX_NUMBER_OF_HISTOGRAM_SAMPLES;
	} else {
		/* we take it all */
		sample_instance_indices =
			array_new_int(n_samples);
		for( size_t sample_idx = 0; sample_idx < n_samples; sample_idx++ ) {
			array_add_int( sample_instance_indices, sample_idx );
		}
	}

	/* remove noisy points and select instances outside a threshold */
	orion_removeIsolatedResponses(
		param,
		features,
		discrim,
		sample_instance_indices,
		&non_isolated_instance_indices );

	n_samples = array_length_int( non_isolated_instance_indices );

	/* set the binning parameters */
	for( size_t feat_idx = 0; feat_idx < features->number_of_features; feat_idx++ ) {
		discrim->min_value[feat_idx] =  FLT_MAX;
		discrim->max_value[feat_idx] = -FLT_MAX;
	}
	for( size_t sample_idx = 0; sample_idx < n_samples; sample_idx++ ) {
		size_t actual_sample_idx =
			array_get_int(non_isolated_instance_indices, sample_idx);
		for( size_t feat_idx = 0; feat_idx < features->number_of_features; feat_idx++ ) {
			pixel_type cur_feature = vector_get_float(
					features->features[feat_idx],
					actual_sample_idx);
			if( cur_feature < discrim->min_value[feat_idx] ) {
				discrim->min_value[feat_idx] = cur_feature;
			}
			if( cur_feature > discrim->max_value[feat_idx] ) {
				discrim->max_value[feat_idx] = cur_feature;
			}
		}
	}
	for( size_t feat_idx = 0; feat_idx < features->number_of_features; feat_idx++ ) {
		discrim->step_size[feat_idx] =
			( discrim->max_value[feat_idx] - discrim->min_value[feat_idx] )
			/ ( param->bins );
		/*[>DEBUG<]LOG_DEBUG( "feat: %d ; min: %f ; max: %f ; bins: %u ; step_size: %e",
				feat_idx,
				discrim->min_value[feat_idx],
				discrim->max_value[feat_idx],
				param->bins,
				discrim->step_size[feat_idx]
				);*/
	}

	/* compute the 2D histogram for edges */
	orion_hist3(param, features, non_isolated_instance_indices, discrim);
	orion_discriminant_function_display( discrim );

	/* normalise the histogram in order to compute the cost function */
	orion_normaliseHistogram(param, discrim);

	array_free_int( non_isolated_instance_indices );
	array_free_int( sample_instance_indices );
}

/* Creates a 2D histogram
 *
 * TODO document
 *
 * See also: MATLAB's hist3 function
 */
void orion_hist3(
		orion_segmentation_param* param,
		orion_features* features,
		array_int* indices,
		orion_discriminant_function* discrim
		) {
	/* we only support 2 features because this is a 2D histogram */
	assert( 2 == features->number_of_features );
	size_t indices_sz = array_length_int(indices);
	size_t* feat_bin_idx;
	NEW_COUNT( feat_bin_idx, size_t, features->number_of_features );

	/* NOTE: histogram is allocated here: if the size of the bins change
	 * for each dimension, then this will need to change */
	orion_histogram_init( discrim, param->bins, param->bins );

	for( int indices_idx = 0; indices_idx < indices_sz; indices_idx++ ) {
		size_t feat_instance_idx = array_get_int( indices, indices_idx );
		for( size_t feat_idx = 0; feat_idx < features->number_of_features; feat_idx++ ) {
			pixel_type cur_feature = vector_get_float(
					features->features[feat_idx],
					feat_instance_idx);
			feat_bin_idx[feat_idx] = floorf(
					( cur_feature - discrim->min_value[feat_idx] )
					/ ( discrim->step_size[feat_idx] )
					);
			if( feat_bin_idx[feat_idx] >= discrim->bin_sz[feat_idx] ) {
				/* max value goes in the last bin */
				feat_bin_idx[feat_idx] = discrim->bin_sz[feat_idx] - 1;
			}
		}
		/* increment by 1 */
		orion_histogram_increment( discrim, feat_bin_idx[0], feat_bin_idx[1] );
	}
}

void orion_normaliseHistogram(
		orion_segmentation_param* param,
		orion_discriminant_function* discrim
		) {
	/* parameter for the smoothing of the Histogram */
	pixel_type sigma = 5;

	/* Apply sigmoid function to normalize the volume. Just in case that we
	 * are not using the multiscale approach */
	for( int hist_idx = 0; hist_idx < orion_histogram_elems(discrim); hist_idx++) {
		/* 1 / (1 + exp(-h)) */
		discrim->norm_histogram[hist_idx] =
			1.0 / ( 1.0 + expf( -(discrim->histogram[hist_idx]) ) );
	}
}
