#ifndef ORION_MULTI_LAP_FILT_H
#define ORION_MULTI_LAP_FILT_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "ndarray/ndarray3.h"
#include "container/array.h"
#include "param/segmentation.h"

/* structs, enums */
typedef struct {
	/* each element contains the maximum response of the Laplacian over the
	 * scales in `laplacian_scales`.
	 */
	ndarray3* laplacian;

	/* each element of scale_for_max_response contains the index of the
	 * scale in `laplacian_scales` for which the response is maximised
	 */
	ndarray3* max_response_at_scale_idx;
} orion_multiscale_laplacian_output;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern orion_multiscale_laplacian_output* orion_multiscaleLaplacianFilter(
		ndarray3* input_volume,
		array_float* laplacian_scales,
		orion_segmentation_param* p );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_MULTI_LAP_FILT_H */
