$(BINDIR)/subsample-volume/SubsampleVolume$(EXEEXT): $(SRCDIR)/subsample-volume/SubsampleVolume.cxx
	$(MKDIR_BIN)
	$(CMAKE.generate) -B$(BINDIR)/subsample-volume -H$(SRCDIR)/subsample-volume
	$(MAKE) -C$(BINDIR)/subsample-volume

BIN_ORION_SEGMENTATION := $(BINDIR)/segmentation/orion-segmentation$(EXEEXT)
$(BIN_ORION_SEGMENTATION): CPPFLAGS += $(ITK_CPPFLAGS) $(VTK_CPPFLAGS)
$(BIN_ORION_SEGMENTATION): LDFLAGS  += $(ITK_LDFLAGS)  $(VTK_LDFLAGS)
$(BIN_ORION_SEGMENTATION): LDLIBS   += $(ITK_LDLIBS)   $(VTK_LDLIBS)
$(BIN_ORION_SEGMENTATION): LDLIBS   += -lstdc++ # needs to add C++ library to link
$(BIN_ORION_SEGMENTATION): \
	$(SRCDIR)/segmentation/orion-segmentation.c \
	$(LIBORION.A)
