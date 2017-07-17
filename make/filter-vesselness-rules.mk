## Filters
$(EIGEN_FRANGI_LIB_OBJ): $(FILTER_FRANGI_OBJ)
$(EIGEN_SATO_LIB_OBJ):   $(FILTER_SATO_OBJ)

$(FILTER_FRANGI_OBJ): $(LIBDIR)/filter/vesselness/frangi/EigenFrangi.cxx
	@$(MKDIR_BUILD.cc)
	$(CMAKE.generate) -B$(BUILDDIR)/filter/vesselness -H$(LIBDIR)/filter/vesselness
	$(MAKE) -C$(BUILDDIR)/filter/vesselness
$(FILTER_SATO_OBJ): $(LIBDIR)/filter/vesselness/sato/EigenSato.cxx
	@$(MKDIR_BUILD.cc)
	$(CMAKE.generate) -B$(BUILDDIR)/filter/vesselness -H$(LIBDIR)/filter/vesselness
	$(MAKE) -C$(BUILDDIR)/filter/vesselness

$(FILTER_BIN): $(SRCDIR)/compute-filter/ComputeFilter.cxx $(FILTER_OBJ)
	$(MKDIR_BIN)
	$(CMAKE.generate) -B$(BINDIR)/compute-filter -H$(SRCDIR)/compute-filter
	$(MAKE) -C$(BINDIR)/compute-filter
