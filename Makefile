include config.mk

HASHMARK = \#

## Source files
BIN_SRC  := src/compute-filter/ComputeFilter.cxx
LIB_SRC  := $(LIBDIR)/ndarray/ndarray3.c  # $(LIBDIR)/hdaf-filter/Makefilter.c
TEST := $(TESTDIR)/canary.c $(TESTDIR)/ndarray/ndarray.c

## Dependency generation
df = $(DEPDIR)/$(*)
MAKEDEPEND.c = gcc -M $(CPPFLAGS) -o $(df).d $<
MKDIR_DEPEND.c = mkdir -p `dirname $(df).d`; $(MAKEDEPEND.c); \
	    $(CP) $(df).d $(df).P; \
	    sed -e 's/$(HASHMARK).*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	        -e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P; \
	    $(RM) $(df).d


## Target files
OBJ_PATHSUBST  = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(1))
TEST_PATHSUBST = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST  = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%$(EXEEXT),$(1))

MKDIR_BUILD = mkdir -p `dirname $(call OBJ_PATHSUBST,$<)`
MKDIR_BIN   = mkdir -p `dirname $(call BIN_PATHSUBST,$<)`

LIB_OBJ:= $(call OBJ_PATHSUBST,$(LIB_SRC))

TEST_OBJ:= $(call TEST_PATHSUBST,$(TEST))

FILTER_OBJ := $(BUILDDIR)/vesselness-filter/libEigenFrangi.a \
	      $(BUILDDIR)/vesselness-filter/libEigenSato.a
FILTER_BIN := $(BINDIR)/compute-filter/ComputeFilter$(EXEEXT)


## Rules
all: $(OUTPUT_DIRS) $(LIB_OBJ) $(FILTER_OBJ) $(FILTER_BIN)

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)

### Output directories
$(OUTPUT_DIRS): # multiple targets
	mkdir -p $@

### Clean
clean:
	find -type f -name '*.o' -delete
	rm -Rf $(OUTPUT_DIRS)

### Implict rules
$(BUILDDIR)/%.o : $(LIBDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILD)
	$(COMPILE.c) -o $@ $<

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
	$(CMAKE.generate) -D LIBDIR=${FULL_LIBDIR} -D BUILDDIR=${FULL_BUILDDIR} -B$(BINDIR)/compute-filter -H$(SRCDIR)/compute-filter
	$(MAKE) -C$(BINDIR)/compute-filter

-include $(SRC:$(LIBDIR)/%.c=$(DEPDIR)/%.P)
