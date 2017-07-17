#ifndef NDARRAY3_FFT_H
#define NDARRAY3_FFT_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

/* external library */
#include <kiss_fft.h>

/* local headers */
#include "ndarray/ndarray3.h"
#include "ndarray/ndarray3_complex.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */

/* These functions calculate the DFT on real n-d data.
 *
 * The Fourier transform of real data is conjugate symmetric and so taking the
 * inverse transform of that data is real-valued.
 *
 * So, given an real n-d input `x`, we have
 *
 *     ndarray3_ifftn_c2r( ndarray3_fftn_r2c( x ) ) == x
 *
 * modulo numerical errors.
 *
 * The data must have even dimensions.
 *
 * See also:
 *    Kiss-FFT:
 *        kiss_fftndr, kiss_fftndri
 *
 *    MATLAB:
 *        ifftn( x, 'symmetric' );
 */
extern ndarray3_complex* ndarray3_fftn_r2c( ndarray3* n );
extern ndarray3* ndarray3_ifftn_c2r( ndarray3_complex* n );

/* These functions allocate memory, but do not require even dimensions */
extern ndarray3_complex* ndarray3_fftn_real( ndarray3* n );
extern ndarray3* ndarray3_ifftn_real( ndarray3_complex* n );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NDARRAY3_FFT_H */
