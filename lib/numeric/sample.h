#ifndef NUMERIC_SAMPLE_H
#define NUMERIC_SAMPLE_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* local headers */
#include "container/array.h"
#include "numeric/random.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern
array_int* array_random_sample_int(
		orion_rand_state_t* rng_state,
		uint32_t sample_size,
		uint32_t population_size);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NUMERIC_SAMPLE_H */
