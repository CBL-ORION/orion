#ifndef DATATYPE_H
#define DATATYPE_H 1

/* type used for calculations */
typedef float             pixel_type;

#ifndef __cplusplus
#include <complex.h>
/* complex is only valid in C99, not C++ */

/* type used for complex number calculations (e.g., FFT) */
typedef float complex     complex_pixel_type;
#endif /* __cplusplus */

/* type used for reading in files */
typedef unsigned short       input_pixel_type;

/* type used for writing out files */
typedef unsigned short       output_pixel_type;

/* number of dimensions for images */
extern const unsigned int PIXEL_NDIMS;

#endif /* DATATYPE_H */
