$(BINDIR)/subsample-volume/SubsampleVolume$(EXEEXT): $(SRCDIR)/subsample-volume/SubsampleVolume.cxx
	$(MKDIR_BIN)
	$(CMAKE.generate) -B$(BINDIR)/subsample-volume -H$(SRCDIR)/subsample-volume
	$(MAKE) -C$(BINDIR)/subsample-volume
