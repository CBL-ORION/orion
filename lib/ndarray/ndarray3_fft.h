#ifndef NDARRAY3_FFT_H
#define NDARRAY3_FFT_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* external library */
#include <kiss_fft.h>

/* local headers */
#include "ndarray/ndarray3.h"

/* structs, enums */
typedef void ndarray3_complex; /* TODO remove this later */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern ndarray3_complex* ndarray3_fftn( ndarray3* n );
extern ndarray3* ndarray3_ifftn_symmetric( ndarray3* n );


#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NDARRAY3_FFT_H */
