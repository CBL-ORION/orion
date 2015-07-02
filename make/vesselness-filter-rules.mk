## Filters

$(BUILDDIR)/vesselness-filter/libEigenFrangi.a: $(LIBDIR)/vesselness-filter/frangi/EigenFrangi.cxx
	@$(MKDIR_BUILD)
	$(CMAKE.generate) -B$(BUILDDIR)/vesselness-filter -H$(LIBDIR)/vesselness-filter
	$(MAKE) -C$(BUILDDIR)/vesselness-filter
$(BUILDDIR)/vesselness-filter/libEigenSato.a: $(LIBDIR)/vesselness-filter/sato/EigenSato.cxx
	@$(MKDIR_BUILD)
	$(CMAKE.generate) -B$(BUILDDIR)/vesselness-filter -H$(LIBDIR)/vesselness-filter
	$(MAKE) -C$(BUILDDIR)/vesselness-filter

$(BINDIR)/compute-filter/ComputeFilter$(EXEEXT): $(SRCDIR)/compute-filter/ComputeFilter.cxx $(FILTER_OBJ)
	$(MKDIR_BIN)
	$(CMAKE.generate) -B$(BINDIR)/compute-filter -H$(SRCDIR)/compute-filter
	$(MAKE) -C$(BINDIR)/compute-filter
