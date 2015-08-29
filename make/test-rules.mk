$(BUILDTESTDIR)/container/array$(EXEEXT): $(BUILDDIR)/container/array.o $(BUILDDIR)/util/util.o

$(BUILDTESTDIR)/container/vector$(EXEEXT): $(BUILDDIR)/container/vector.o $(BUILDDIR)/util/util.o

$(BUILDTESTDIR)/orion3-config-parser/parse-file$(EXEEXT): $(BUILDDIR)/util/util.o $(BUILDDIR)/simple-log/simplelog.o \
	$(BUILDDIR)/param/param.o $(BUILDDIR)/param/orion3.o \
	$(BUILDDIR)/orion3-config-parser/parser.o $(BUILDDIR)/container/array.o

$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): LDFLAGS += -lstdc++ # needs to add C++ library to link to lib libIntegrationITK.a
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): \
		$(BUILDDIR)/io/format/mhd.o \
		$(BUILDDIR)/ndarray/array_ndarray3.o \
		$(BUILDDIR)/ndarray/ndarray3.o \
		$(BUILDDIR)/util/util.o \
		$(BUILDDIR)/integration/itk/libIntegrationITK.a \
		| $(TEST_DATA_NPF023)


include temp/itk-config.mk
ITK_LDFLAGS += -msse2 -rdynamic
ITK_LDLIBS := \
	/usr/local/lib/libitkdouble-conversion-4.8.a /usr/local/lib/libitksys-4.8.a \
	/usr/local/lib/libitkvnl_algo-4.8.a /usr/local/lib/libitkvnl-4.8.a \
	/usr/local/lib/libitkv3p_netlib-4.8.a /usr/local/lib/libITKCommon-4.8.a \
	/usr/local/lib/libitkNetlibSlatec-4.8.a /usr/local/lib/libITKStatistics-4.8.a \
	/usr/local/lib/libITKIOImageBase-4.8.a /usr/local/lib/libITKIOBMP-4.8.a \
	/usr/local/lib/libITKIOBioRad-4.8.a /usr/local/lib/libITKEXPAT-4.8.a \
	/usr/local/lib/libitkzlib-4.8.a /usr/local/lib/libitkgdcmDICT-4.8.a \
	/usr/local/lib/libitkgdcmMSFF-4.8.a /usr/local/lib/libITKIOGDCM-4.8.a \
	/usr/local/lib/libITKIOGIPL-4.8.a /usr/local/lib/libitkjpeg-4.8.a \
	/usr/local/lib/libITKIOJPEG-4.8.a /usr/local/lib/libitktiff-4.8.a \
	/usr/local/lib/libITKIOTIFF-4.8.a /usr/local/lib/libITKIOLSM-4.8.a \
	/usr/local/lib/libITKMetaIO-4.8.a /usr/local/lib/libITKIOMeta-4.8.a \
	/usr/local/lib/libITKznz-4.8.a /usr/local/lib/libITKniftiio-4.8.a \
	/usr/local/lib/libITKIONIFTI-4.8.a /usr/local/lib/libITKNrrdIO-4.8.a \
	/usr/local/lib/libITKIONRRD-4.8.a /usr/local/lib/libitkpng-4.8.a \
	/usr/local/lib/libITKIOPNG-4.8.a /usr/local/lib/libITKIOStimulate-4.8.a \
	/usr/local/lib/libITKIOVTK-4.8.a /usr/local/lib/libITKMesh-4.8.a \
	/usr/local/lib/libITKSpatialObjects-4.8.a /usr/local/lib/libITKPath-4.8.a \
	/usr/local/lib/libITKLabelMap-4.8.a /usr/local/lib/libITKQuadEdgeMesh-4.8.a \
	/usr/local/lib/libITKOptimizers-4.8.a /usr/local/lib/libITKPolynomials-4.8.a \
	/usr/local/lib/libITKBiasCorrection-4.8.a /usr/local/lib/libITKBioCell-4.8.a \
	/usr/local/lib/libITKDICOMParser-4.8.a /usr/local/lib/libITKIOXML-4.8.a \
	/usr/local/lib/libITKIOSpatialObjects-4.8.a /usr/local/lib/libITKFEM-4.8.a \
	/usr/local/lib/libITKgiftiio-4.8.a /usr/local/lib/libITKIOMesh-4.8.a \
	/usr/local/lib/libitkhdf5_cpp-4.8.a /usr/local/lib/libitkhdf5-4.8.a \
	/usr/local/lib/libITKIOCSV-4.8.a /usr/local/lib/libITKIOIPL-4.8.a \
	/usr/local/lib/libITKIOGE-4.8.a /usr/local/lib/libITKIOSiemens-4.8.a \
	/usr/local/lib/libITKIOHDF5-4.8.a /usr/local/lib/libITKIOMRC-4.8.a \
	/usr/local/lib/libITKIOTransformBase-4.8.a \
	/usr/local/lib/libITKIOTransformHDF5-4.8.a \
	/usr/local/lib/libITKIOTransformInsightLegacy-4.8.a \
	/usr/local/lib/libITKIOTransformMatlab-4.8.a \
	/usr/local/lib/libITKKLMRegionGrowing-4.8.a /usr/local/lib/libITKVTK-4.8.a \
	/usr/local/lib/libITKWatersheds-4.8.a /usr/local/lib/libITKOptimizersv4-4.8.a \
	/usr/local/lib/libITKVideoCore-4.8.a /usr/local/lib/libITKVideoIO-4.8.a \
	/usr/local/lib/libitkgdcmMSFF-4.8.a /usr/local/lib/libitkgdcmDICT-4.8.a \
	/usr/local/lib/libitkgdcmIOD-4.8.a /usr/local/lib/libitkgdcmDSED-4.8.a \
	/usr/local/lib/libitkgdcmCommon-4.8.a /usr/local/lib/libitkgdcmjpeg8-4.8.a \
	/usr/local/lib/libitkgdcmjpeg12-4.8.a /usr/local/lib/libitkgdcmjpeg16-4.8.a \
	/usr/local/lib/libitkgdcmopenjpeg-4.8.a /usr/local/lib/libitkgdcmcharls-4.8.a \
	/usr/local/lib/libitkgdcmuuid-4.8.a /usr/local/lib/libITKIOTIFF-4.8.a \
	/usr/local/lib/libitktiff-4.8.a /usr/local/lib/libitkjpeg-4.8.a \
	/usr/local/lib/libITKNrrdIO-4.8.a /usr/local/lib/libitkpng-4.8.a \
	/usr/local/lib/libITKPolynomials-4.8.a /usr/local/lib/libITKIOXML-4.8.a \
	/usr/local/lib/libITKMetaIO-4.8.a /usr/local/lib/libITKgiftiio-4.8.a \
	/usr/local/lib/libITKEXPAT-4.8.a /usr/local/lib/libITKniftiio-4.8.a \
	/usr/local/lib/libITKznz-4.8.a /usr/local/lib/libITKIOGE-4.8.a \
	/usr/local/lib/libITKIOIPL-4.8.a /usr/local/lib/libitkhdf5_cpp-4.8.a \
	/usr/local/lib/libitkhdf5-4.8.a /usr/local/lib/libitkzlib-4.8.a \
	/usr/local/lib/libITKIOTransformBase-4.8.a \
	/usr/local/lib/libITKSpatialObjects-4.8.a /usr/local/lib/libITKMesh-4.8.a \
	/usr/local/lib/libITKPath-4.8.a /usr/local/lib/libITKOptimizers-4.8.a \
	/usr/local/lib/libITKStatistics-4.8.a /usr/local/lib/libitkNetlibSlatec-4.8.a \
	/usr/local/lib/libITKIOImageBase-4.8.a /usr/local/lib/libITKVideoCore-4.8.a \
	/usr/local/lib/libITKCommon-4.8.a /usr/local/lib/libitkdouble-conversion-4.8.a \
	/usr/local/lib/libitksys-4.8.a /usr/local/lib/libITKVNLInstantiation-4.8.a \
	/usr/local/lib/libitkvnl_algo-4.8.a /usr/local/lib/libitkv3p_lsqr-4.8.a \
	/usr/local/lib/libitkvnl-4.8.a /usr/local/lib/libitkvcl-4.8.a \
	/usr/local/lib/libitkv3p_netlib-4.8.a -lm -lpthread -ldl -lm

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
test: CPPFLAGS += $(TEST_CPPFLAGS) $(ITK_CPPFLAGS)
test: LDFLAGS  += $(TEST_LDFLAGS) $(ITK_LDFLAGS)
test: LDLIBS   += $(TEST_LDLIBS) $(ITK_LDLIBS)
