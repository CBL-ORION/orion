#include <cstdlib>
#include <iostream>

#include <tap/basic.h>

#include "itkImageFileReader.h"
#include "itkMetaImageIOFactory.h"
#include "itkImageRegionConstIterator.h"

#include "filter/vesselness/PixelAccessors.hxx"
#include "filter/vesselness/sato/EigenSato.hxx"
#include "integration/itk/itk.hxx"
#include "config/itkdatatype.hxx"
#include "io/format/mhd.h"
#include "util/util.h"

int main(void) {
	plan( 1 + 1 );

	char mhd_filename[] = "test-data/ITK/HeadMRVolume/HeadMRVolume.mhd";

	/* enable the MetaImage IO reading */
	typedef itk::ImageFileReader< InternalImageType >     ReaderType;
	itk::MetaImageIOFactory::RegisterOneFactory();

	/* read in the MetaImage volume using ITK */
	ReaderType::Pointer m_Reader =  ReaderType::New();
	m_Reader->SetFileName( mhd_filename );
	m_Reader->Update();
	InternalImageType::Pointer vol_itk = m_Reader->GetOutput();

	/* read in the same MetaImage volume using ORION code */
	ndarray3* vol_orion = orion_read_mhd( mhd_filename );



	{
		/* This code tests that the volumes index to the same values
		 * when looping over all (i,j,k) coordinates in each respective
		 * volume. */
		bool same_volume_by_index = true;

		NDARRAY3_LOOP_OVER_START( vol_orion, i,j,k) {
			InternalImageType::IndexType ind = { i, j, k };
			float64 pix_itk = vol_itk->GetPixel( ind );
			float64 pix_orion = ndarray3_get( vol_orion, i,j,k );

			if( pix_itk != pix_orion ) {
				same_volume_by_index = false;
				break;
			}
		} NDARRAY3_LOOP_OVER_END;

		ok( same_volume_by_index, "The volume read by ITK and ORION are the same when compared using indexing.");
	}


	{
		/* This code compares the contiguous memory layout of the
		 * volumes by using an iterator for ITK and pointer for ORION. */
		bool same_volume_by_iterator = true;
		itk::ImageRegionConstIterator<InternalImageType> vol_itk_it(
				vol_itk,
				vol_itk->GetLargestPossibleRegion());
		pixel_type* vol_orion_ptr = vol_orion->p;
		size_t vol_idx = 0;

		while( !vol_itk_it.IsAtEnd() ) {
			/*[>DEBUG<]printf("ITK: %f ; ORION: %f\n", vol_itk_it.Get(), *vol_orion_ptr);*/
			if( vol_itk_it.Get() != *vol_orion_ptr ) {
				same_volume_by_iterator = false;
				break;
			}

			++vol_itk_it;
			vol_orion_ptr++;
			vol_idx++;
		}

		ok( same_volume_by_iterator, "The volume read by ITK and ORION are the same when compared using pointer access.");
	}

	ndarray3_free( vol_orion );
}
