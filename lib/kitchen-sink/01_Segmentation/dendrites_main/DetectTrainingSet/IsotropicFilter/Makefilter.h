#ifndef ORION_MAKEFILTER_H
#define ORION_MAKEFILTER_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "ndarray/ndarray3.h"

/* structs, enums */
typedef enum {
	orion_Makefilter_FLAG_A,
	orion_Makefilter_FLAG_B,
	orion_Makefilter_FLAG_C
} orion_Makefilter_flag;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern ndarray3* orion_Makefilter(
		size_t nx, size_t ny, size_t nz,
		int hdaf_approx_degree,
		float scale_factor,
		orion_Makefilter_flag flag);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_MAKEFILTER_H */
