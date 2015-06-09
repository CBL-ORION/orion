
// Software Guide : BeginCodeSnippet
#include "itkConnectedThresholdImageFilter.h"
// Software Guide : EndCodeSnippet


#include "itkImage.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"

#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkImageAdaptor.h"
#include "PixelAccessors.h"
#include "itkSymmetricEigenAnalysisImageFilter.h"
#include "itkCastImageFilter.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"


const int nSigmas = 1;

int main( int argc, char *argv[])
{
  if( argc <2 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage sigma1" << std::endl;
	std::cerr << "with no mhd extension"<<std::endl;
    return 1;
    }

  typedef   unsigned short  InputPixelType;

  typedef   float           InternalPixelType;
  const     unsigned int    Dimension = 3;

  typedef itk::Image< InternalPixelType, Dimension >	InternalImageType;

  // We instantiate reader and writer types
  typedef   itk::ImageFileReader< InternalImageType >	ReaderType;
  typedef   itk::ImageFileWriter<  InternalImageType  > WriterType;


  typedef   itk::HessianRecursiveGaussianImageFilter<
                            InternalImageType >           HessianFilterType;
  typedef   HessianFilterType::OutputImageType            HessianImageType;
  typedef   HessianImageType::PixelType                   HessianPixelType;

  typedef   itk::FixedArray< float, 3 >
                                                          EigenValueArrayType;
  typedef  itk::Image< EigenValueArrayType, HessianImageType::ImageDimension >
                                                          EigenValueImageType;
  typedef  itk::ImageAdaptor<  EigenValueImageType,
								EigenValueAccessor< EigenValueArrayType > >	  ImageAdaptorType;
  typedef   itk::SymmetricEigenAnalysisImageFilter<
								HessianImageType, EigenValueImageType >     EigenAnalysisFilterType;
  typedef itk::CastImageFilter< ImageAdaptorType,
								InternalImageType >	  CastImageFilterType;

     const std::string mhd = ".mhd";
     const std::string sigmaString = ".Sigma";


     const std::string eigenValuesString1 = ".EigVal1";
     const std::string eigenValuesString2 = ".EigVal2";
     const std::string eigenValuesString3 = ".EigVal3";

	 const std::string inputVolumeFilename = argv[1];
	  std::string outputVolumeEigenValue_1_Filename = inputVolumeFilename + eigenValuesString1 ;
	  std::string outputVolumeEigenValue_2_Filename = inputVolumeFilename + eigenValuesString2 ;
	  std::string outputVolumeEigenValue_3_Filename = inputVolumeFilename + eigenValuesString3 ;

	 itk::FixedArray< float, nSigmas >  sigmasValuesArray;


	sigmasValuesArray[0] = atof( argv[2] );

	 WriterType::Pointer m_InternalWriter = WriterType::New();


	ReaderType::Pointer m_Reader =  ReaderType::New();
	m_Reader->SetFileName( (inputVolumeFilename+mhd).c_str());
    m_Reader->Update();

	HessianFilterType::Pointer  m_Hessian = HessianFilterType::New();
	m_Hessian->SetInput( m_Reader->GetOutput() );
	m_Hessian->SetNormalizeAcrossScale( true );

  // Compute eigen values.. order them in ascending order
  EigenAnalysisFilterType::Pointer m_EigenFilter = EigenAnalysisFilterType::New();
  m_EigenFilter->SetDimension( HessianPixelType::Dimension );
  m_EigenFilter->OrderEigenValuesBy(EigenAnalysisFilterType::FunctorType::OrderByMagnitude);


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




  for(int i=0; i< sigmasValuesArray.Size(); i++)
  {
	 outputVolumeEigenValue_1_Filename = outputVolumeEigenValue_1_Filename  + sigmaString + "." +  argv[i+2] + mhd;
     outputVolumeEigenValue_2_Filename = outputVolumeEigenValue_2_Filename  + sigmaString + "." +  argv[i+2] + mhd;
     outputVolumeEigenValue_3_Filename = outputVolumeEigenValue_3_Filename  + sigmaString + "." +  argv[i+2] + mhd;

	  //std::cout<<"Computing Hessian matrix set to  "<<sigmasValuesArray[i]<<"..."<<std::endl;
		m_Hessian->SetSigma(sigmasValuesArray[i]);
		m_Hessian->Update();
	  //std::cout<<"Computing Hessian set to  "<<sigmasValuesArray[i]<<"...Done"<<std::endl;

	  //std::cout<<"Computing Eigenvalues from the Hessian matrix... "<<std::endl;
	m_EigenFilter->SetInput( m_Hessian->GetOutput() );
	m_EigenFilter->OrderEigenValuesBy( EigenAnalysisFilterType::FunctorType::OrderByMagnitude );
	m_EigenFilter->Update();
	//std::cout<<"Computing Eigenvalues from the Hessian matrix done... "<<std::endl;

	accessor1.SetEigenIdx( 0 );
	m_EigenAdaptor1->SetImage( m_EigenFilter->GetOutput() );
	m_EigenAdaptor1->SetPixelAccessor( accessor1 );

	accessor2.SetEigenIdx( 1 );
	m_EigenAdaptor2->SetImage( m_EigenFilter->GetOutput() );
	m_EigenAdaptor2->SetPixelAccessor( accessor2 );

    accessor3.SetEigenIdx( 2 );
	m_EigenAdaptor3->SetImage( m_EigenFilter->GetOutput() );
	m_EigenAdaptor3->SetPixelAccessor( accessor3 );

    m_EigenCastfilter1->SetInput( m_EigenAdaptor1 );
    m_EigenCastfilter2->SetInput( m_EigenAdaptor2 );
    m_EigenCastfilter3->SetInput( m_EigenAdaptor3 );

	//std::cout<<"Writing EigenValues for  "<<sigmasValuesArray[i]<<"..."<<std::endl;
	m_EigenCastfilter1->Update();
	m_InternalWriter->SetInput( m_EigenCastfilter1->GetOutput() );
	m_InternalWriter->SetFileName( outputVolumeEigenValue_1_Filename.c_str());
	m_InternalWriter->Update();


	m_EigenCastfilter2->Update();
	m_InternalWriter->SetInput( m_EigenCastfilter2->GetOutput() );
	m_InternalWriter->SetFileName( outputVolumeEigenValue_2_Filename.c_str() );
	m_InternalWriter->Update();


	m_EigenCastfilter3->Update();
	m_InternalWriter->SetInput( m_EigenCastfilter3->GetOutput() );
	m_InternalWriter->SetFileName( outputVolumeEigenValue_3_Filename.c_str());
	m_InternalWriter->Update();
	//std::cout<<"Writing EigenValues for  "<<sigmasValuesArray[i]<<"...Done"<<std::endl;

	// outputVolumeEigenValue_1_Filename = inputVolumeFilename + eigenValuesString1  ;
    // outputVolumeEigenValue_2_Filename = inputVolumeFilename + eigenValuesString2  ;
    // outputVolumeEigenValue_3_Filename = inputVolumeFilename + eigenValuesString3  ;
  }


  //std::cout<<"Computing Eigenvalues... Done." << std::endl;
  return 0;
}




