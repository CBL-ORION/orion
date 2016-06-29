#ifndef ORION_VIS_H
#define ORION_VIS_H 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
  /* Need to initialise because we are building without CMake:
   * <http://www.vtk.org/Wiki/VTK/VTK_6_Migration/Factories_now_require_defines>
   */
  #include <vtkAutoInit.h>
  VTK_MODULE_INIT(vtkRenderingOpenGL);
  VTK_MODULE_INIT(vtkInteractionStyle);
  VTK_MODULE_INIT(vtkRenderingFreeType);
  /*VTK_MODULE_INIT(vtkRenderingFreeTypeOpenGL);*/
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
#endif

/* local headers */
#include "segmentation/orion_discriminant.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes */
extern
void orion_discriminant_function_display( orion_discriminant_function* discrim );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ORION_VIS_H */
