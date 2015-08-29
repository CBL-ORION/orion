$(BUILDTESTDIR)/container/array$(EXEEXT): $(BUILDDIR)/container/array.o $(BUILDDIR)/util/util.o

$(BUILDTESTDIR)/container/vector$(EXEEXT): $(BUILDDIR)/container/vector.o $(BUILDDIR)/util/util.o

$(BUILDTESTDIR)/orion3-config-parser/parse-file$(EXEEXT): $(BUILDDIR)/util/util.o $(BUILDDIR)/simple-log/simplelog.o \
	$(BUILDDIR)/param/param.o $(BUILDDIR)/param/orion3.o \
	$(BUILDDIR)/orion3-config-parser/parser.o $(BUILDDIR)/container/array.o

$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): LDFLAGS += -lstdc++ # needs to add C++ library to link to lib libIntegrationITK.a
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): \
		$(BUILDDIR)/util/util.o \
		$(BUILDDIR)/ndarray/ndarray3.o \
		$(BUILDDIR)/ndarray/array_ndarray3.o \
		$(BUILDDIR)/io/format/mhd.o \
		$(BUILDDIR)/integration/itk/libIntegrationITK.a \
		$(BUILDDIR)/filter/vesselness/libEigenFrangi.a \
		$(BUILDDIR)/filter/vesselness/libEigenSato.a \
		| $(TEST_DATA_NPF023)

ITK_VERSION_SUFFIX := -4.8
ITK_LDFLAGS += -msse2 -rdynamic
ITK_LDLIBS := \
	-litkdouble-conversion$(ITK_VERSION_SUFFIX) \
	-litksys$(ITK_VERSION_SUFFIX) \
	-litkvnl_algo$(ITK_VERSION_SUFFIX) \
	-litkvnl$(ITK_VERSION_SUFFIX) \
	-litkv3p_netlib$(ITK_VERSION_SUFFIX) \
	-lITKCommon$(ITK_VERSION_SUFFIX) \
	-litkNetlibSlatec$(ITK_VERSION_SUFFIX) \
	-lITKStatistics$(ITK_VERSION_SUFFIX) \
	-lITKIOImageBase$(ITK_VERSION_SUFFIX) \
	-lITKIOBMP$(ITK_VERSION_SUFFIX) \
	-lITKIOBioRad$(ITK_VERSION_SUFFIX) \
	-lITKEXPAT$(ITK_VERSION_SUFFIX) \
	-litkzlib$(ITK_VERSION_SUFFIX) \
	-litkgdcmDICT$(ITK_VERSION_SUFFIX) \
	-litkgdcmMSFF$(ITK_VERSION_SUFFIX) \
	-lITKIOGDCM$(ITK_VERSION_SUFFIX) \
	-lITKIOGIPL$(ITK_VERSION_SUFFIX) \
	-litkjpeg$(ITK_VERSION_SUFFIX) \
	-lITKIOJPEG$(ITK_VERSION_SUFFIX) \
	-litktiff$(ITK_VERSION_SUFFIX) \
	-lITKIOTIFF$(ITK_VERSION_SUFFIX) \
	-lITKIOLSM$(ITK_VERSION_SUFFIX) \
	-lITKMetaIO$(ITK_VERSION_SUFFIX) \
	-lITKIOMeta$(ITK_VERSION_SUFFIX) \
	-lITKznz$(ITK_VERSION_SUFFIX) \
	-lITKniftiio$(ITK_VERSION_SUFFIX) \
	-lITKIONIFTI$(ITK_VERSION_SUFFIX) \
	-lITKNrrdIO$(ITK_VERSION_SUFFIX) \
	-lITKIONRRD$(ITK_VERSION_SUFFIX) \
	-litkpng$(ITK_VERSION_SUFFIX) \
	-lITKIOPNG$(ITK_VERSION_SUFFIX) \
	-lITKIOStimulate$(ITK_VERSION_SUFFIX) \
	-lITKIOVTK$(ITK_VERSION_SUFFIX) \
	-lITKMesh$(ITK_VERSION_SUFFIX) \
	-lITKSpatialObjects$(ITK_VERSION_SUFFIX) \
	-lITKPath$(ITK_VERSION_SUFFIX) \
	-lITKLabelMap$(ITK_VERSION_SUFFIX) \
	-lITKQuadEdgeMesh$(ITK_VERSION_SUFFIX) \
	-lITKOptimizers$(ITK_VERSION_SUFFIX) \
	-lITKPolynomials$(ITK_VERSION_SUFFIX) \
	-lITKBiasCorrection$(ITK_VERSION_SUFFIX) \
	-lITKBioCell$(ITK_VERSION_SUFFIX) \
	-lITKDICOMParser$(ITK_VERSION_SUFFIX) \
	-lITKIOXML$(ITK_VERSION_SUFFIX) \
	-lITKIOSpatialObjects$(ITK_VERSION_SUFFIX) \
	-lITKFEM$(ITK_VERSION_SUFFIX) \
	-lITKgiftiio$(ITK_VERSION_SUFFIX) \
	-lITKIOMesh$(ITK_VERSION_SUFFIX) \
	-litkhdf5_cpp$(ITK_VERSION_SUFFIX) \
	-litkhdf5$(ITK_VERSION_SUFFIX) \
	-lITKIOCSV$(ITK_VERSION_SUFFIX) \
	-lITKIOIPL$(ITK_VERSION_SUFFIX) \
	-lITKIOGE$(ITK_VERSION_SUFFIX) \
	-lITKIOSiemens$(ITK_VERSION_SUFFIX) \
	-lITKIOHDF5$(ITK_VERSION_SUFFIX) \
	-lITKIOMRC$(ITK_VERSION_SUFFIX) \
	-lITKIOTransformBase$(ITK_VERSION_SUFFIX) \
	-lITKIOTransformHDF5$(ITK_VERSION_SUFFIX) \
	-lITKIOTransformInsightLegacy$(ITK_VERSION_SUFFIX) \
	-lITKIOTransformMatlab$(ITK_VERSION_SUFFIX) \
	-lITKKLMRegionGrowing$(ITK_VERSION_SUFFIX) \
	-lITKVTK$(ITK_VERSION_SUFFIX) \
	-lITKWatersheds$(ITK_VERSION_SUFFIX) \
	-lITKOptimizersv4$(ITK_VERSION_SUFFIX) \
	-lITKVideoCore$(ITK_VERSION_SUFFIX) \
	-lITKVideoIO$(ITK_VERSION_SUFFIX) \
	-litkgdcmMSFF$(ITK_VERSION_SUFFIX) \
	-litkgdcmDICT$(ITK_VERSION_SUFFIX) \
	-litkgdcmIOD$(ITK_VERSION_SUFFIX) \
	-litkgdcmDSED$(ITK_VERSION_SUFFIX) \
	-litkgdcmCommon$(ITK_VERSION_SUFFIX) \
	-litkgdcmjpeg8$(ITK_VERSION_SUFFIX) \
	-litkgdcmjpeg12$(ITK_VERSION_SUFFIX) \
	-litkgdcmjpeg16$(ITK_VERSION_SUFFIX) \
	-litkgdcmopenjpeg$(ITK_VERSION_SUFFIX) \
	-litkgdcmcharls$(ITK_VERSION_SUFFIX) \
	-litkgdcmuuid$(ITK_VERSION_SUFFIX) \
	-lITKIOTIFF$(ITK_VERSION_SUFFIX) \
	-litktiff$(ITK_VERSION_SUFFIX) \
	-litkjpeg$(ITK_VERSION_SUFFIX) \
	-lITKNrrdIO$(ITK_VERSION_SUFFIX) \
	-litkpng$(ITK_VERSION_SUFFIX) \
	-lITKPolynomials$(ITK_VERSION_SUFFIX) \
	-lITKIOXML$(ITK_VERSION_SUFFIX) \
	-lITKMetaIO$(ITK_VERSION_SUFFIX) \
	-lITKgiftiio$(ITK_VERSION_SUFFIX) \
	-lITKEXPAT$(ITK_VERSION_SUFFIX) \
	-lITKniftiio$(ITK_VERSION_SUFFIX) \
	-lITKznz$(ITK_VERSION_SUFFIX) \
	-lITKIOGE$(ITK_VERSION_SUFFIX) \
	-lITKIOIPL$(ITK_VERSION_SUFFIX) \
	-litkhdf5_cpp$(ITK_VERSION_SUFFIX) \
	-litkhdf5$(ITK_VERSION_SUFFIX) \
	-litkzlib$(ITK_VERSION_SUFFIX) \
	-lITKIOTransformBase$(ITK_VERSION_SUFFIX) \
	-lITKSpatialObjects$(ITK_VERSION_SUFFIX) \
	-lITKMesh$(ITK_VERSION_SUFFIX) \
	-lITKPath$(ITK_VERSION_SUFFIX) \
	-lITKOptimizers$(ITK_VERSION_SUFFIX) \
	-lITKStatistics$(ITK_VERSION_SUFFIX) \
	-litkNetlibSlatec$(ITK_VERSION_SUFFIX) \
	-lITKIOImageBase$(ITK_VERSION_SUFFIX) \
	-lITKVideoCore$(ITK_VERSION_SUFFIX) \
	-lITKCommon$(ITK_VERSION_SUFFIX) \
	-litkdouble-conversion-4.8 \
	-litksys$(ITK_VERSION_SUFFIX) \
	-lITKVNLInstantiation$(ITK_VERSION_SUFFIX) \
	-litkvnl_algo$(ITK_VERSION_SUFFIX) \
	-litkv3p_lsqr$(ITK_VERSION_SUFFIX) \
	-litkvnl$(ITK_VERSION_SUFFIX) \
	-litkvcl$(ITK_VERSION_SUFFIX) \
	-litkv3p_netlib$(ITK_VERSION_SUFFIX) \
	-lm -lpthread -ldl -lm

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
test: CPPFLAGS += $(TEST_CPPFLAGS)
test: LDFLAGS  += $(TEST_LDFLAGS)
test: LDLIBS   += $(TEST_LDLIBS)

$(BUILDTESTDIR)/integration/itk/itk: CPPFLAGS += $(TEST_CPPFLAGS) $(ITK_CPPFLAGS)
$(BUILDTESTDIR)/integration/itk/itk: LDFLAGS  += $(TEST_LDFLAGS) $(ITK_LDFLAGS)
$(BUILDTESTDIR)/integration/itk/itk: LDLIBS   += $(TEST_LDLIBS) $(ITK_LDLIBS)
