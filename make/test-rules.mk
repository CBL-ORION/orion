$(BUILDTESTDIR)/container/array$(EXEEXT): $(BUILDDIR)/container/array.o $(BUILDDIR)/util/util.o

$(BUILDTESTDIR)/container/vector$(EXEEXT): $(BUILDDIR)/container/vector.o $(BUILDDIR)/util/util.o

$(BUILDTESTDIR)/orion3-config-parser/parse-file$(EXEEXT): $(BUILDDIR)/util/util.o $(BUILDDIR)/util/string.o \
	$(BUILDDIR)/simple-log/simplelog.o \
	$(BUILDDIR)/param/param.o $(BUILDDIR)/param/orion3.o \
	$(BUILDDIR)/orion3-config-parser/parser.o $(BUILDDIR)/container/array.o \
	$(BUILDDIR)/io/util/util.o

$(BUILDTESTDIR)/io/path/path$(EXEEXT): $(BUILDDIR)/io/path/path.o $(BUILDDIR)/util/util.o $(BUILDDIR)/util/string.o $(BUILDDIR)/container/array.o

$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): CPPFLAGS += $(ITK_CPPFLAGS)
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): LDFLAGS  += $(ITK_LDFLAGS)
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): LDLIBS   += $(ITK_LDLIBS)
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): LDLIBS   += -lstdc++ # needs to add C++ library to link to lib libIntegrationITK.a
$(BUILDTESTDIR)/integration/itk/itk$(EXEEXT): \
		$(BUILDDIR)/util/util.o \
		$(BUILDDIR)/io/path/path.o $(BUILDDIR)/util/string.o \
		$(BUILDDIR)/ndarray/ndarray3.o \
		$(BUILDDIR)/ndarray/array_ndarray3.o \
		$(BUILDDIR)/container/array.o \
		$(BUILDDIR)/io/format/mhd.o \
		$(BUILDDIR)/io/util/util.o \
		$(BUILDDIR)/simple-log/simplelog.o \
		$(BUILDDIR)/integration/itk/libIntegrationITK.a \
		$(BUILDDIR)/filter/vesselness/libEigenFrangi.a \
		$(BUILDDIR)/filter/vesselness/libEigenSato.a \
		| $(TEST_DATA_NPF023)


$(BUILDTESTDIR)/io/mhd$(EXEEXT): \
		$(BUILDDIR)/util/util.o $(BUILDDIR)/util/string.o \
		$(BUILDDIR)/ndarray/ndarray3.o \
		$(BUILDDIR)/container/array.o \
		$(BUILDDIR)/io/format/mhd.o \
		$(BUILDDIR)/io/util/util.o \
		$(BUILDDIR)/io/path/path.o

$(BUILDTESTDIR)/numeric/func_factorial$(EXEEXT): \
		$(BUILDDIR)/util/util.o \
		$(BUILDDIR)/numeric/func.o
$(BUILDTESTDIR)/numeric/func_polyeval_horners$(EXEEXT): \
		$(BUILDDIR)/util/util.o \
		$(BUILDDIR)/numeric/func.o
$(BUILDTESTDIR)/kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/hdaf$(EXEEXT): \
		$(BUILDDIR)/util/util.o \
		$(BUILDDIR)/numeric/func.o \
		$(BUILDDIR)/ndarray/ndarray3.o \
		$(BUILDDIR)/kitchen-sink/01_Segmentation/dendrites_main/DetectTrainingSet/IsotropicFilter/hdaf.o


test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
test: CPPFLAGS += $(TEST_CPPFLAGS)
test: LDFLAGS  += $(TEST_LDFLAGS)
test: LDLIBS   += $(TEST_LDLIBS)
