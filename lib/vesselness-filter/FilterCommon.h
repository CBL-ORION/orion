#ifndef FILTERCOMMON_H
#define FILTERCOMMON_H

#include "itkImage.h"
#include "itkFixedArray.h"

#include "config/datatype.h"

typedef itk::Image< InternalPixelType, Dimension >	InternalImageType;
typedef itk::FixedArray<InternalImageType::Pointer, Dimension > OutputImageArrayType;

#endif /* FILTERCOMMON_H */
