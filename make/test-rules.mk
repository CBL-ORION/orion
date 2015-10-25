ITK_MHD_TEST := $(BUILDTESTDIR)/integration/itk/mhd$(EXEEXT)
ITK_INTEGRATION_TESTS := \
	$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT) \
	$(BUILDTESTDIR)/kitchen-sink/01_Segmentation/dendrites_main/ExtractFeatures/computeEigenvaluesGaussianFilter$(EXEEXT) \
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

$(TEST_OBJ): $(LIBORION.A)

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
test: CPPFLAGS += $(TEST_CPPFLAGS)
test: LDFLAGS  += $(TEST_LDFLAGS)
test: LDLIBS   += $(TEST_LDLIBS)
