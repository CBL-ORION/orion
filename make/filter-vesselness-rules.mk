## Filters

$(BUILDDIR)/filter/vesselness/libEigenFrangi.a: $(LIBDIR)/filter/vesselness/frangi/EigenFrangi.cxx
	@$(MKDIR_BUILD)
	$(CMAKE.generate) -B$(BUILDDIR)/filter/vesselness -H$(LIBDIR)/filter/vesselness
	$(MAKE) -C$(BUILDDIR)/filter/vesselness
$(BUILDDIR)/filter/vesselness/libEigenSato.a: $(LIBDIR)/filter/vesselness/sato/EigenSato.cxx
	@$(MKDIR_BUILD)
	$(CMAKE.generate) -B$(BUILDDIR)/filter/vesselness -H$(LIBDIR)/filter/vesselness
	$(MAKE) -C$(BUILDDIR)/filter/vesselness

$(FILTER_BIN): $(SRCDIR)/compute-filter/ComputeFilter.cxx $(FILTER_OBJ)
	$(MKDIR_BIN)
	$(CMAKE.generate) -B$(BINDIR)/compute-filter -H$(SRCDIR)/compute-filter
	$(MAKE) -C$(BINDIR)/compute-filter
