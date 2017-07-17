/* Need to initialise because we are building without CMake:
 * <http://www.vtk.org/Wiki/VTK/VTK_6_Migration/Factories_now_require_defines>
 */
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingFreeTypeOpenGL);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);

#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper.h>
#include <vtkActor2D.h>
#include <vtkImageSlice.h>

static void CreateColorImage(vtkImageData*);

int main(int, char *[])
{
	vtkSmartPointer<vtkImageData> colorImage = vtkSmartPointer<vtkImageData>::New();
	CreateColorImage(colorImage);

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

		return EXIT_SUCCESS;
}

void CreateColorImage(vtkImageData* image)
{
	unsigned int dim = 20;

		image->SetDimensions(dim, dim, 1);
#if VTK_MAJOR_VERSION <= 5
	image->SetNumberOfScalarComponents(3);
	image->SetScalarTypeToUnsignedChar();
	image->AllocateScalars();
#else
	image->AllocateScalars(VTK_UNSIGNED_CHAR,3);
#endif
	for(unsigned int x = 0; x < dim; x++)
	{
		for(unsigned int y = 0; y < dim; y++)
		{
			unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
			if(x < dim/2)
			{
				pixel[0] = 255;
				pixel[1] = 0;
			}
			else
			{
				pixel[0] = 0;
				pixel[1] = 255;
			}

				pixel[2] = 0;
		}
	}

		image->Modified();
}
