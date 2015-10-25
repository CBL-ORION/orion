#include "integration/itk/itk.hxx"

/* ITK headers */
#include "itkImage.h"
#include "itkFixedArray.h"
#include "itkImportImageFilter.h"
#include "itkStatisticsImageFilter.h"

#include "simple-log/simplelog.h"

#include "FilterCommon.hxx"
#include "EigenSato.hxx"
#include "EigenFrangi.hxx"

/* _orion_convert_ndarray3_to_itkImage
 *
 * [Internal function]
 *
 * Converts a 3D dimensional volume stored in the ndarray3* volume into an
 * itk::Image::Pointer.
 *
 * This allows for passing ndarray3* data into filters written in ITK.
 */
InternalImageType::Pointer _orion_convert_ndarray3_to_itkImage(ndarray3* vol) {
	/* Convert the pointer to the image data using an ImportImageFilter.
	 * See <http://www.itk.org/Wiki/ITK/Examples/IO/ImportImageFilter> for
	 * more information.  */
	typedef itk::ImportImageFilter< InternalPixelType, Dimension >    ImportFilterType;
	ImportFilterType::Pointer importFilter = ImportFilterType::New();

	ImportFilterType::SizeType  size;
	size[0] = vol->sz[0];
	size[1] = vol->sz[1];
	size[2] = vol->sz[2];

	ImportFilterType::IndexType start;
	start.Fill( 0 );

	ImportFilterType::RegionType region;
	region.SetIndex( start );
	region.SetSize(  size  );

	importFilter->SetRegion( region );

	double origin[ Dimension ];
	origin[0] = 0.0;    // X coordinate
	origin[1] = 0.0;    // Y coordinate
	origin[2] = 0.0;    // Z coordinate

	importFilter->SetOrigin( origin );

	double spacing[ Dimension ];
	spacing[0] = vol->spacing[0];    // along X direction
	spacing[1] = vol->spacing[1];    // along Y direction
	spacing[2] = vol->spacing[2];    // along Z direction

	importFilter->SetSpacing( spacing );

	const size_t number_of_pixels = size[0] * size[1] * size[2];
	InternalPixelType* buffer = vol->p;
	const bool itkImportImageFilter_will_own_buffer = false;
	importFilter->SetImportPointer( buffer, number_of_pixels,
			itkImportImageFilter_will_own_buffer );
	importFilter->Update();

	InternalImageType::Pointer vol_itk = importFilter->GetOutput();

	return vol_itk;
}

ndarray3* _orion_convert_itkImage_to_ndarray3( InternalImageType::Pointer vol_itk ) {
	InternalImageType::PixelType* pixel_data = vol_itk->GetBufferPointer();
	InternalImageType::RegionType region = vol_itk->GetLargestPossibleRegion();
	InternalImageType::SizeType sz = region.GetSize();

	InternalImageType::PixelContainer* cont = vol_itk->GetPixelContainer();
	/* this data is now owned by ndarray3 and will be free'd by ndarray3 */
	cont->SetContainerManageMemory(false);
	ndarray3* n = ndarray3_buffer( pixel_data, sz[0], sz[1], sz[2] );

	return n;
}

array_ndarray3* _orion_convert_itkFixedArray_to_array_ndarray( OutputImageArrayType arr_itk ) {
	/* get the size of the arr_itk and create an array_ndarray3* of the
	 * same size */
	OutputImageArrayType::SizeType sz = arr_itk.Size();
	array_ndarray3* arr_eig = array_new_ndarray3((size_t)sz);

	/* fill `arr_eig` with the ndarray3* volumes converted from `arr_eig_itk`'s
	 * elements */
	for( int i = 0; i < sz; i++ ) {
		ndarray3* nd = _orion_convert_itkImage_to_ndarray3( arr_itk[i] );
		array_add_ndarray3( arr_eig, nd );
	}

	return arr_eig;
}

float64 _orion_itkImage_sum_over_all_float64( InternalImageType::Pointer vol_itk ) {
	typedef itk::StatisticsImageFilter<InternalImageType> StatisticsImageFilterType;

	StatisticsImageFilterType::Pointer statisticsImageFilter = StatisticsImageFilterType::New();
	statisticsImageFilter->SetInput(vol_itk);
	statisticsImageFilter->Update();

	return statisticsImageFilter->GetSum();
}

array_ndarray3* orion_filter_method_sato( ndarray3* vol, float sigma ) {
	InternalImageType::Pointer vol_itk = _orion_convert_ndarray3_to_itkImage( vol );
	/*[>DEBUG<]std::cout << vol_itk << std::endl;*/

	LOG_INFO("Computing the Sato vessellness feature filter");
	OutputImageArrayType arr_eig_itk  = ComputeSato( vol_itk, sigma );
	/*[>DEBUG<]std::cout << arr_eig_itk[0] << std::endl;*/

	LOG_INFO("Converting the results of the Sato filter array");
	array_ndarray3* arr_eig = _orion_convert_itkFixedArray_to_array_ndarray( arr_eig_itk );
	return arr_eig;
}

array_ndarray3* orion_filter_method_frangi( ndarray3* vol, float sigma ) {
	InternalImageType::Pointer vol_itk = _orion_convert_ndarray3_to_itkImage( vol );
	/*[>DEBUG<]std::cout << vol_itk << std::endl;*/

	LOG_INFO("Computing the Frangi vessellness feature filter");
	OutputImageArrayType arr_eig_itk  = ComputeFrangi( vol_itk, sigma );

	LOG_INFO("Converting the results of the Frangi filter array");
	array_ndarray3* arr_eig = _orion_convert_itkFixedArray_to_array_ndarray( arr_eig_itk );
	return arr_eig;
}

array_ndarray3* orion_filter_method_single_eigenvalue( ndarray3* vol, float sigma ) {
	WARN_UNIMPLEMENTED;
}
