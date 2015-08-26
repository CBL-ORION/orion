## Targets
FILTER_FRANGI_OBJ := $(BUILDDIR)/filter/vesselness/libEigenFrangi.a
FILTER_SATO_OBJ := $(BUILDDIR)/filter/vesselness/libEigenSato.a
FILTER_OBJ := $(FILTER_FRANGI_OBJ) $(FILTER_SATO_OBJ)

FILTER_BIN := $(BINDIR)/compute-filter/ComputeFilter$(EXEEXT)
