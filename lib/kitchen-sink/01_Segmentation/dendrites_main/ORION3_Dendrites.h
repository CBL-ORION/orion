#ifndef ORION3_DENDRITES_H
#define ORION3_DENDRITES_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "param/segmentation.h"
#include "ndarray/ndarray3.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern void orion_ORION3_Dendrites(orion_segmentation_param* param, ndarray3* vol);


#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION3_DENDRITES_H */
