#ifndef EIGENFRANGI_H
#define EIGENFRANGI_H 1


#include "itkConnectedThresholdImageFilter.h"
#include "itkImage.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"

#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkImageAdaptor.h"
#include "PixelAccessors.hxx"
#include "itkSymmetricEigenAnalysisImageFilter.h"
#include "itkCastImageFilter.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "FilterCommon.hxx"

OutputImageArrayType ComputeFrangi( InternalImageType::Pointer inputVolume, float sigma );

#endif /* EIGENFRANGI_H */
