#include "itkImage.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"

#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkImageAdaptor.h"
#include "PixelAccessors.hxx"
#include "itkSymmetricEigenAnalysisImageFilter.h"
#include "itkCastImageFilter.h"

#include "EigenSato.hxx"

OutputImageArrayType ComputeSato( const InternalImageType::Pointer inputVolume, float sigma)
{
     typedef   itk::HessianRecursiveGaussianImageFilter< InternalImageType >       HessianFilterType;
     typedef   HessianFilterType::OutputImageType                                  HessianImageType;
     typedef   HessianImageType::PixelType                                         HessianPixelType;

     typedef   itk::FixedArray< float, 3 >
           EigenValueArrayType;
     typedef  itk::Image< EigenValueArrayType, HessianImageType::ImageDimension >
           EigenValueImageType;
     typedef  itk::ImageAdaptor<  EigenValueImageType, EigenValueAccessor<   EigenValueArrayType > >  ImageAdaptorType;
     typedef   itk::SymmetricEigenAnalysisImageFilter<  HessianImageType, EigenValueImageType >     EigenAnalysisFilterType;
     typedef itk::CastImageFilter< ImageAdaptorType, InternalImageType >	                    CastImageFilterType;

     // itk::FixedArray< float, nSigmas >  sigmasValuesArray;

     HessianFilterType::Pointer  m_Hessian = HessianFilterType::New();
     m_Hessian->SetInput( inputVolume );
     m_Hessian->SetNormalizeAcrossScale( true );

     // Compute eigen values.. order them in ascending order
     EigenAnalysisFilterType::Pointer m_EigenFilter = EigenAnalysisFilterType::New();
     m_EigenFilter->SetDimension( HessianPixelType::Dimension );

    // Create an adaptor and plug the output to the parametric space
     ImageAdaptorType::Pointer m_EigenAdaptor1 = ImageAdaptorType::New();
     EigenValueAccessor< EigenValueArrayType > accessor1;

     ImageAdaptorType::Pointer m_EigenAdaptor2 = ImageAdaptorType::New();
     EigenValueAccessor< EigenValueArrayType > accessor2;

     ImageAdaptorType::Pointer m_EigenAdaptor3 = ImageAdaptorType::New();
     EigenValueAccessor< EigenValueArrayType > accessor3;

     // m_EigenCastfilter1 will give the eigen values with the maximum eigen
     // value. m_EigenCastfilter3 will give the eigen values with the
     // minimum eigen value.
     CastImageFilterType::Pointer m_EigenCastfilter1 = CastImageFilterType::New();

     CastImageFilterType::Pointer m_EigenCastfilter2 = CastImageFilterType::New();

     CastImageFilterType::Pointer m_EigenCastfilter3 = CastImageFilterType::New();




     m_Hessian->SetSigma(sigma);
     m_Hessian->Update();

     m_EigenFilter->SetInput( m_Hessian->GetOutput() );
     m_EigenFilter->OrderEigenValuesBy( EigenAnalysisFilterType::FunctorType::OrderByValue );
     m_EigenFilter->Update();


     accessor1.SetEigenIdx( 0 );
     m_EigenAdaptor1->SetImage( m_EigenFilter->GetOutput() );
     m_EigenAdaptor1->SetPixelAccessor( accessor1 );

     accessor2.SetEigenIdx( 1 );
     m_EigenAdaptor2->SetImage( m_EigenFilter->GetOutput() );
     m_EigenAdaptor2->SetPixelAccessor( accessor2 );

     accessor3.SetEigenIdx( 2 );
     m_EigenAdaptor3->SetImage( m_EigenFilter->GetOutput() );
     m_EigenAdaptor3->SetPixelAccessor( accessor3 );

     m_EigenCastfilter1->SetInput( m_EigenAdaptor3 );
     m_EigenCastfilter2->SetInput( m_EigenAdaptor2 );
     m_EigenCastfilter3->SetInput( m_EigenAdaptor1 );


     m_EigenCastfilter1->Update();
     m_EigenCastfilter2->Update();
     m_EigenCastfilter3->Update();

     OutputImageArrayType output;
     output[0]= m_EigenCastfilter1->GetOutput();
     output[1]= m_EigenCastfilter2->GetOutput();
     output[2]= m_EigenCastfilter3->GetOutput();

     return output;
}
