#ifndef FILTERCOMMON_H
#define FILTERCOMMON_H

#include "itkImage.h"
#include "itkFixedArray.h"

typedef   unsigned short  InputPixelType;

typedef   float           InternalPixelType;
const     unsigned int    Dimension = 3;

typedef itk::Image< InternalPixelType, Dimension >	InternalImageType;
typedef itk::FixedArray<InternalImageType::Pointer, Dimension > OutputImageArrayType;

#endif /* FILTERCOMMON_H */
