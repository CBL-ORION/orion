#ifndef PARAM_SEGMENTATION_H
#define PARAM_SEGMENTATION_H 1

#include <stdint.h>
#include <stdbool.h>

#include "container/array.h"
#include "util/float.h"
#include "numeric/random.h"

typedef struct {
	array_float* scales;     /* sigma */
	bool multiscale;
	size_t number_of_stacks; /* length of volume_names */

	orion_rand_state_t* rng_state;

#define ATTR( NAME, TYPE ) \
	bool has_ ## NAME; \
	TYPE NAME;
#include "segmentation_attr_table.h"
#undef ATTR

} orion_segmentation_param;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define ATTR( NAME, TYPE ) \
	extern \
	void orion_segmentation_param_set_ ## NAME ( orion_segmentation_param* param , TYPE new_ ## NAME );
#include "segmentation_attr_table.h"
#undef ATTR

extern orion_segmentation_param* orion_segmentation_param_new();
extern void orion_segmentation_param_free(orion_segmentation_param* param);
extern void orion_segmentation_param_set_default_scales( orion_segmentation_param* param );
extern void orion_segmentation_param_dump( orion_segmentation_param* param );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* PARAM_SEGMENTATION_H */
