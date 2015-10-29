#ifndef NDARRAY3_FFT_H
#define NDARRAY3_FFT_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* local headers */
#include "ndarray/ndarray3.h"

/* structs, enums */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern ndarray3* ndarray3_fftn( ndarray3* n );
extern ndarray3* ndarray3_ifftn_symmetric( ndarray3* n );



#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NDARRAY3_FFT_H */
