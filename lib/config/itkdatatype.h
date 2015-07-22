#ifndef ITK_DATATYPE_H
#define ITK_DATATYPE_H 1

#include "config/datatype.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"


/* standard names for ITK filters */
typedef input_pixel_type_t      InputPixelType;
typedef pixel_type_t         InternalPixelType; /* standard name for ITK filters */
typedef output_pixel_type_t    OutputPixelType; /* standard name for ITK filters */

const   unsigned int   Dimension = 3; /* should be PIXEL_NDIMS, but needed for ITK templates */

typedef itk::Image< InputPixelType,    Dimension >   InputImageType;
typedef itk::Image< InternalPixelType, Dimension >   InternalImageType;
typedef itk::Image< OutputPixelType,   Dimension >   OutputImageType;

typedef itk::ImageFileReader< InputImageType  >  ReaderType;
typedef itk::ImageFileWriter< OutputImageType >  WriterType;

#endif /* ITK_DATATYPE_H */

