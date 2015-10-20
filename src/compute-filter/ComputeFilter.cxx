
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
#include "PixelAccessors.hxx"
#include "itkSymmetricEigenAnalysisImageFilter.h"
#include "itkCastImageFilter.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "FilterCommon.hxx"
#include "EigenSato.hxx"
#include "EigenFrangi.hxx"



int main( int argc, char *argv[])
{
	if( argc < 3 ) {
		std::cerr << "Missing Parameters " << std::endl;
		std::cerr << "Usage: " << argv[0];
		std::cerr << "[sato|frangi] inputImage sigma1" << std::endl;
		std::cerr << "with no mhd extension"<<std::endl;
		return 1;
	}

	/* Get the type of filter*/
	const std::string filtertype = argv[1];
	/*Get the filename parameter */
	const std::string inputVolumeFilename = argv[2];
	/*Get the sigma parameter */
	const std::string sigmaParamString = argv[3];
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

	OutputImageArrayType outputImages;

	if (filtertype == "sato")
	{
		/********************************/
		/* Compute the Sato eigenvalues */
		/********************************/
		outputImages = ComputeSato(m_Reader->GetOutput(), sigma );
	}
	else
	{
		/**********************************/
		/* Compute the Frangi eigenvalues */
		/**********************************/
		outputImages = ComputeFrangi(m_Reader->GetOutput(), sigma );
	}


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
