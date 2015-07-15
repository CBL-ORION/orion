#ifndef DATATYPE_H
#define DATATYPE_H 1

/* type used for calculations */
typedef float             pixel_type_t;
typedef pixel_type_t      InternalPixelType; /* standard name for ITK filters */

/* type used for reading in files */
typedef unsigned short       input_pixel_type_t;
typedef input_pixel_type_t   InputPixelType; /* standard name for ITK filters */

/* number of dimensions for images */
const     unsigned int    Dimension = 3;

#endif /* DATATYPE_H */
