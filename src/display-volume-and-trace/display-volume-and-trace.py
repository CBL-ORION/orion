#!/usr/bin/python

import vtk

WIDTH = 640
HEIGHT = 480

#segmented_volume = '/home/zaki/r/experiment-confocal-radii_20141121/V081005Ab3_Segmentation__MultiscaleDENDRITES_s_1_2_3_4_5_6_7_8_9_10_b_500_thr_0.5_tra_0.995_min_c8000.mhd'
#ground_truth_centreline = '/home/zaki/r/data/vol_and_trace/081005A.SuperVolume.FourStacks/trace/20070607_final.vtk'

segmented_volume = 'test-data/DIADEM/NPF/03_Reconstruction/rec_NPF026/Raw_reg.mhd'
ground_truth_centreline = 'test-data/DIADEM/NPF/03_Reconstruction/rec_NPF026/Raw_reg.swc.vtk'

def test():
	ren = vtk.vtkRenderer()
	renWin = vtk.vtkRenderWindow()
	renWin.AddRenderer(ren)
	renWin.SetSize(WIDTH, HEIGHT)

	# create a renderwindowinteractor
	iren = vtk.vtkRenderWindowInteractor()
	iren.SetRenderWindow(renWin)

	level = 0.5
	antique_white = [ 0.9804, 0.9216, 0.8431 ]

	cone = vtk.vtkConeSource()
	for cone in [cone]:
		for s in [cone]:
			s.SetResolution( 60 )
			s.SetCenter( -2,0,0 )
		coneMapper = vtk.vtkPolyDataMapper()
		for m in [coneMapper]:
			m.SetInputConnection( cone.GetOutputPort() )
		coneActor = vtk.vtkActor()
		for a in [coneActor]:
			a.SetMapper( coneMapper )

	centerline = vtk.vtkPolyDataReader()
	for centerline in [centerline]:
		for r in [centerline]:
			r.SetFileName( ground_truth_centreline )
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
			r.SetFileName( segmented_volume )
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

		segmentation_filter = vtk.vtkContourFilter()
		for f in [segmentation_filter]:
			f.SetInputData( segmentation.GetOutput() )
			f.SetValue( 0, level )
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


test()
