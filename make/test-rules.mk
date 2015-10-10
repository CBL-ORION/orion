$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): CPPFLAGS += $(ITK_CPPFLAGS)
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): LDFLAGS  += $(ITK_LDFLAGS)
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): LDLIBS   += $(ITK_LDLIBS)
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): LDLIBS   += -lstdc++ # needs to add C++ library to link to lib libIntegrationITK.a
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): \
		$(BUILDDIR)/integration/itk/libIntegrationITK.a \
		$(BUILDDIR)/filter/vesselness/libEigenFrangi.a \
		$(BUILDDIR)/filter/vesselness/libEigenSato.a \
		| $(TEST_DATA_NPF023)

$(TEST_OBJ): $(LIBORION.A)

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
test: CPPFLAGS += $(TEST_CPPFLAGS)
test: LDFLAGS  += $(TEST_LDFLAGS)
test: LDLIBS   += $(TEST_LDLIBS)
