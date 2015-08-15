$(BINDIR)/subsample-volume/SubsampleVolume$(EXEEXT): $(SRCDIR)/subsample-volume/SubsampleVolume.cxx
	$(MKDIR_BIN)
	$(CMAKE.generate) -B$(BINDIR)/subsample-volume -H$(SRCDIR)/subsample-volume
	$(MAKE) -C$(BINDIR)/subsample-volume

$(BINDIR)/segmentation/orion-segmentation$(EXEEXT): $(SRCDIR)/segmentation/orion-segmentation.c \
		$(BUILDDIR)/simple-log/simplelog.o $(BUILDDIR)/util/util.o \
		$(BUILDDIR)/param/segmentation.o $(BUILDDIR)/param/io.o \
		$(BUILDDIR)/param/param.o \
		$(BUILDDIR)/container/array.o
