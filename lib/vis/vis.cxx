#include "vis.hxx"

#include <cstdint>

void _orion_discriminant_function_to_vtkImageData(
	orion_discriminant_function* discrim,
	vtkImageData* image ) {

	image->SetDimensions(discrim->bin_sz[0], discrim->bin_sz[1], 1);

	uint32_t image_scalar_dim = 1;
#if VTK_MAJOR_VERSION <= 5
	image->SetNumberOfScalarComponents(image_scalar_dim);
	image->SetScalarTypeToInt();
	image->AllocateScalars();
#else
	image->AllocateScalars(VTK_INT, image_scalar_dim);
#endif
	int* vtkImagePixel = static_cast<int*>( image->GetScalarPointer(0,0,0) );
	size_t* orion_disc_bins = discrim->histogram;
	size_t hist_nelems = orion_histogram_elems( discrim );
	for(size_t idx = 0; idx < hist_nelems; idx++, orion_disc_bins++, vtkImagePixel += image_scalar_dim ) {
		vtkImagePixel[0] = *orion_disc_bins;
	}
}


void orion_discriminant_function_display( orion_discriminant_function* discrim ) {
	vtkSmartPointer<vtkImageData> colorImage = vtkSmartPointer<vtkImageData>::New();
	_orion_discriminant_function_to_vtkImageData(discrim, colorImage);

	vtkSmartPointer<vtkImageMapper> imageMapper = vtkSmartPointer<vtkImageMapper>::New();
#if VTK_MAJOR_VERSION <= 5
	imageMapper->SetInputConnection(colorImage->GetProducerPort());
#else
	imageMapper->SetInputData(colorImage);
#endif
	imageMapper->SetColorWindow(255);
	imageMapper->SetColorLevel(127.5);

	vtkSmartPointer<vtkActor2D> imageActor = vtkSmartPointer<vtkActor2D>::New();
	imageActor->SetMapper(imageMapper);
	imageActor->SetPosition(20, 20);

		// Setup renderers
		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

		// Setup render window
		vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

		renderWindow->AddRenderer(renderer);

		// Setup render window interactor
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

		vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

		renderWindowInteractor->SetInteractorStyle(style);

		// Render and start interaction
		renderWindowInteractor->SetRenderWindow(renderWindow);

		//renderer->AddViewProp(imageActor);
		renderer->AddActor2D(imageActor);

		renderWindow->Render();
	renderWindowInteractor->Start();


}
