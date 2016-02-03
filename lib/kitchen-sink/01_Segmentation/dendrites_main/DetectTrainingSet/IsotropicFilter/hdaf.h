#ifndef ORION_HDAF_H
#define ORION_HDAF_H 1

/* local headers */
#include "ndarray/ndarray3.h"

/* structs, enums */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern ndarray3* orion_hdaf(
		int hdaf_approx_degree,
		float scaling_constant,
		ndarray3* x);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_HDAF_H */
