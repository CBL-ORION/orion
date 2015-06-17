
// Software Guide : BeginCodeSnippet
#include "itkConnectedThresholdImageFilter.h"
// Software Guide : EndCodeSnippet

//SATO
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


/* Typedefs*/
typedef   unsigned short  InputPixelType;

typedef   float           InternalPixelType;
const     unsigned int    Dimension = 3;

typedef itk::Image< InternalPixelType, Dimension >	InternalImageType;
typedef itk::FixedArray<InternalImageType::Pointer, Dimension > OutputImageArrayType;

const int nSigmas = 1;

/*Prototypes*/
OutputImageArrayType ComputeSato( InternalImageType::Pointer inputVolume, float sigma );


int main( int argc, char *argv[])
{
       if( argc < 2 ) {
               std::cerr << "Missing Parameters " << std::endl;
	       std::cerr << "Usage: " << argv[0];
	       std::cerr << " inputImage sigma1" << std::endl;
	       std::cerr << "with no mhd extension"<<std::endl;
	       return 1;
       }

       /*Get the filename parameter */
       const std::string inputVolumeFilename = argv[1];
       /*Get the sigma parameter */
       const std::string sigmaParamString = argv[2];
       float sigma = atof( sigmaParamString.c_str() ); 

       // We instantiate reader and writer types
       typedef   itk::ImageFileReader< InternalImageType >	ReaderType;
       typedef   itk::ImageFileWriter<  InternalImageType  > WriterType;

       /*Extension for the image type */
       const std::string mhd = ".mhd";

       
       /*****************/
       /* Read the data */
       /*****************/
       	ReaderType::Pointer m_Reader =  ReaderType::New();
	m_Reader->SetFileName( (inputVolumeFilename+mhd).c_str());
	m_Reader->Update();

	
	/**********************************/
	/* Compute the Sato eigenvalues */
	/**********************************/
	OutputImageArrayType outputImages = ComputeSato(m_Reader->GetOutput(), sigma );




	/**********************/
	/* Write out the data */
	/**********************/
	const std::string sigmaString = ".Sigma";
	const std::string eigenValuesString1 = ".EigVal1";
	const std::string eigenValuesString2 = ".EigVal2";
	const std::string eigenValuesString3 = ".EigVal3";


	 std::string outputVolumeEigenValue_1_Filename = inputVolumeFilename + eigenValuesString1 ;
	 std::string outputVolumeEigenValue_2_Filename = inputVolumeFilename + eigenValuesString2 ;
	 std::string outputVolumeEigenValue_3_Filename = inputVolumeFilename + eigenValuesString3 ;

	 
	  WriterType::Pointer m_InternalWriter = WriterType::New();
	  
	  
	  outputVolumeEigenValue_1_Filename = outputVolumeEigenValue_1_Filename  + sigmaString + "." + sigmaParamString + mhd;
	  outputVolumeEigenValue_2_Filename = outputVolumeEigenValue_2_Filename  + sigmaString + "." + sigmaParamString + mhd;
	  outputVolumeEigenValue_3_Filename = outputVolumeEigenValue_3_Filename  + sigmaString + "." + sigmaParamString + mhd;


	  m_InternalWriter->SetInput( outputImages[0] );
	  m_InternalWriter->SetFileName( outputVolumeEigenValue_1_Filename.c_str());
	  m_InternalWriter->Update();
	
	  m_InternalWriter->SetInput( outputImages[1] );
	  m_InternalWriter->SetFileName( outputVolumeEigenValue_2_Filename.c_str() );
	  m_InternalWriter->Update();

	  m_InternalWriter->SetInput( outputImages[2] );
	  m_InternalWriter->SetFileName( outputVolumeEigenValue_3_Filename.c_str());
	  m_InternalWriter->Update();

	  return 0;
}


OutputImageArrayType ComputeSato( InternalImageType::Pointer inputVolume, float sigma)
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





