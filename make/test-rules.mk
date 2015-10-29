ITK_MHD_TEST := $(BUILDTESTDIR)/integration/itk/mhd$(EXEEXT)
ITK_INTEGRATION_TESTS := \
	$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT) \
	$(BUILDTESTDIR)/kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeEigenvaluesGaussianFilter$(EXEEXT) \
	$(BUILDTESTDIR)/kitchen-sink/01_Segmentation/dendrites_main/ORION3_Dendrites$(EXEEXT) \
	$(ITK_MHD_TEST)

$(ITK_INTEGRATION_TESTS): CPPFLAGS += $(ITK_CPPFLAGS)
$(ITK_INTEGRATION_TESTS): LDFLAGS  += $(ITK_LDFLAGS)
$(ITK_INTEGRATION_TESTS): LDLIBS   += $(ITK_LDLIBS)
$(ITK_INTEGRATION_TESTS): LDLIBS   += -lstdc++ # needs to add C++ library to link to lib libIntegrationITK.a

$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT) : $(LIBORION.A) \
		| $(TEST_DATA_NPF023)

$(ITK_MHD_TEST): CPPFLAGS += $(TEST_CPPFLAGS) -Ilib/filter/vesselness
$(ITK_MHD_TEST): LDFLAGS  += $(TEST_LDFLAGS)
$(ITK_MHD_TEST): LDLIBS   += $(TEST_LDLIBS)
$(ITK_MHD_TEST): $(LIBORION.A)

TEST_OBJ += $(ITK_MHD_TEST)

NDARRAY_FFT_TEST := $(BUILDTESTDIR)/ndarray/ndarray3_fft$(EXEEXT)
$(NDARRAY_FFT_TEST): CPPFLAGS += $(KISS_FFT_CPPFLAGS)
$(NDARRAY_FFT_TEST): LDFLAGS += $(KISS_FFT_LDFLAGS)
$(NDARRAY_FFT_TEST): LDLIBS += $(KISS_FFT_LDLIBS)

$(TEST_OBJ): $(LIBORION.A)

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
$(TEST_OBJ) test: CPPFLAGS += $(TEST_CPPFLAGS)
$(TEST_OBJ) test: LDFLAGS  += $(TEST_LDFLAGS)
$(TEST_OBJ) test: LDLIBS   += $(TEST_LDLIBS)
