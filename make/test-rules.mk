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

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
test: CPPFLAGS += $(TEST_CPPFLAGS)
test: LDFLAGS  += $(TEST_LDFLAGS)
test: LDLIBS   += $(TEST_LDLIBS)

$(BUILDTESTDIR)/integration/itk/itk: CPPFLAGS += $(TEST_CPPFLAGS) $(ITK_CPPFLAGS)
$(BUILDTESTDIR)/integration/itk/itk: LDFLAGS  += $(TEST_LDFLAGS) $(ITK_LDFLAGS)
$(BUILDTESTDIR)/integration/itk/itk: LDLIBS   += $(TEST_LDLIBS) $(ITK_LDLIBS)
