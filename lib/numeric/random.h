#ifndef ORION_NUMERIC_RANDOM_H
#define ORION_NUMERIC_RANDOM_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* local headers */
#include "util/util.h"
#include "numeric/kiss99_rng.h"

/* structs, enums */
typedef kiss99_rng_state orion_rand_state_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern
float64 orion_rand_uniform_dist(orion_rand_state_t* state);
extern void kiss99_rng_init(kiss99_rng_state* state);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_NUMERIC_RANDOM_H */
