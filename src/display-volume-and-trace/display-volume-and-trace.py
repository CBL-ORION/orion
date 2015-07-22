#!/usr/bin/python

import vtk
import sys, os

WIDTH = 640
HEIGHT = 480

def main(argv):
	if len(argv) < 3:
		sys.stderr.write("Usage: %s <volume.mhd> <trace.vtk>\n" % argv[0])
		return 1

	segmented_volume_filename, trace_filename = argv[1:3]

	for filename in [ segmented_volume_filename, trace_filename ]:
		if not os.path.exists(filename):
			sys.stderr.write("file '%s' not found\n" % filename)
			return 1

	ren = vtk.vtkRenderer()
	renWin = vtk.vtkRenderWindow()
	renWin.AddRenderer(ren)
	renWin.SetSize(WIDTH, HEIGHT)

	# create a renderwindowinteractor
	iren = vtk.vtkRenderWindowInteractor()
	iren.SetRenderWindow(renWin)

	antique_white = [ 0.9804, 0.9216, 0.8431 ]
	line_width = 5

	centerline = vtk.vtkPolyDataReader()
	for centerline in [centerline]:
		for r in [centerline]:
			r.SetFileName( trace_filename )
			r.ReadAllVectorsOn()
			r.ReadAllScalarsOn()
			r.Update()
			centerline_mapper = vtk.vtkPolyDataMapper()
			for m in [centerline_mapper]:
				m.SetInputData( centerline.GetOutput() )
			centreline_actor = vtk.vtkActor()
			for a in [centreline_actor]:
				a.SetMapper( centerline_mapper )
				a.GetProperty().SetColor( *antique_white )
				a.GetProperty().SetLineWidth( line_width );

	# Create transfer mapping scalar value to opacity
	opacity_transfer_function = vtk.vtkPiecewiseFunction()
	for tf in [opacity_transfer_function]:
		tf.AddPoint( 20 , 0.0)
		tf.AddPoint( 255 , 0.2)
	# Create transfer mapping scalar value to color
	color_transfer_function = vtk.vtkColorTransferFunction()
	for tf in [color_transfer_function]:
		tf.AddRGBPoint(0.0, 0.0, 0.0, 0.0)
		tf.AddRGBPoint(64.0, 0.2, 0.0, 0.0)
		tf.AddRGBPoint(128.0, 0.0, 0.0, 1.0)
		tf.AddRGBPoint( 192.0, 0.0, 1.0, 0.0)
		tf.AddRGBPoint( 255.0, 0.0, 0.2, 0.0)
		tf.SetColorSpaceToDiverging()
	# The property describes how the data will look
	volume_property = vtk.vtkVolumeProperty()
	for vp in [volume_property]:
		vp.SetColor(color_transfer_function)
		vp.SetScalarOpacity(opacity_transfer_function)

	segmentation = vtk.vtkMetaImageReader()
	for segmentation in [segmentation]:
		for r in [segmentation]:
			r.SetFileName( segmented_volume_filename )
			r.Update()

		segmentation_outline_filter = vtk.vtkOutlineFilter()
		for f in [segmentation_outline_filter]:
			f.SetInputData( segmentation.GetOutput() )
		segmentation_outline_mapper = vtk.vtkPolyDataMapper()
		for m in [segmentation_outline_mapper]:
			m.SetInputConnection( segmentation_outline_filter.GetOutputPort() )
		segmentation_outline_actor = vtk.vtkActor()
		for a in [segmentation_outline_actor]:
			a.SetMapper( segmentation_outline_mapper )

		segmentation_mapper = vtk.vtkSmartVolumeMapper()
		for m in [segmentation_mapper]:
			m.SetInputData( segmentation.GetOutput() )
		segmentation_actor = vtk.vtkVolume()
		for a in [segmentation_actor]:
			a.SetMapper( segmentation_mapper )
			a.SetProperty( volume_property )




		for actor in [ centreline_actor, segmentation_actor, segmentation_outline_actor]:
			ren.AddActor( actor )

	iren.Initialize()
	renWin.Render()

	iren.Start()


if __name__ == "__main__":
    sys.exit(main(sys.argv))
