include make/helper.mk
include make/config.mk

## Source files
BIN_SRC  := src/compute-filter/ComputeFilter.cxx
LIB_SRC  := $(LIBDIR)/ndarray/ndarray3.c  # $(LIBDIR)/hdaf-filter/Makefilter.c
TEST := $(TESTDIR)/canary.c $(TESTDIR)/ndarray/ndarray.c $(TESTDIR)/liborion3mat/test.c

include make/autodep.mk

## Target files
OBJ_PATHSUBST  = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(1))
TEST_PATHSUBST = $(patsubst $(TESTDIR)/%.c,$(BUILDTESTDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST  = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%$(EXEEXT),$(1))

MKDIR_BUILD = mkdir -p `dirname $(call OBJ_PATHSUBST,$<)`
MKDIR_BIN   = mkdir -p `dirname $(call BIN_PATHSUBST,$<)`

LIB_OBJ:= $(call OBJ_PATHSUBST,$(LIB_SRC))

TEST_OBJ:= $(call TEST_PATHSUBST,$(TEST))

include make/vesselness-filter-config.mk
include make/vaa3d-plugin-config.mk
include make/liborion3mat-config.mk

## Rules
all: $(OUTPUT_DIRS) $(LIB_OBJ) \
	$(FILTER_OBJ) $(FILTER_BIN) \
	$(VAA3D_ORION_MATLAB_LIB_OBJ)

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
test: CPPFLAGS += $(TEST_CPPFLAGS)
test: LDFLAGS  += $(TEST_LDFLAGS)
test: LDLIBS   += $(TEST_LDLIBS)

### Output directories
$(OUTPUT_DIRS): # multiple targets
	mkdir -p $@

### Clean
clean:
	-find -type f -name '*.o' -delete
	-rm -Rf $(OUTPUT_DIRS)
	-rm $(VAA3D_ORION_MATLAB_LIB_OBJ)

### Implict rules
$(BUILDDIR)/%.o : $(LIBDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILD)
	$(COMPILE.c) -o $@ $<

-include $(SRC:$(LIBDIR)/%.c=$(DEPDIR)/%.P)

$(BUILDTESTDIR)/ndarray/ndarray: $(BUILDDIR)/ndarray/ndarray3.o

$(BUILDTESTDIR)/liborion3mat/test: ${ORION3MAT_LIB_OBJ}
$(BUILDTESTDIR)/liborion3mat/test: CFLAGS   += $(LIBORION3MAT_CFLAGS)   $(MCR_CFLAGS)
$(BUILDTESTDIR)/liborion3mat/test: CPPFLAGS += $(LIBORION3MAT_CPPFLAGS) $(MCR_CPPFLAGS)
$(BUILDTESTDIR)/liborion3mat/test: LDFLAGS  += $(LIBORION3MAT_LDFLAGS)  $(MCR_LDFLAGS)
$(BUILDTESTDIR)/liborion3mat/test: LDLIBS   += $(LIBORION3MAT_LDLIBS)   $(MCR_LDLIBS)

run.with-matlab-env: $(BUILDTESTDIR)/liborion3mat/test
	# Running using MATLAB for loading dynamic libraries
	LD_PRELOAD=${MATLAB_LD_PRELOAD} LD_LIBRARY_PATH=${ORION3MAT_LIB_OBJ_PATH}:${MATLAB_LD_LIBRARY_PATH} $<
run.with-mcr-env: $(BUILDTESTDIR)/liborion3mat/test
	# Running using MATLAB Compiler Runtime for loading dynamic libraries
	LD_PRELOAD=${MCR_LD_PRELOAD} LD_LIBRARY_PATH=${ORION3MAT_LIB_OBJ_PATH}:${MCR_LD_LIBRARY_PATH} $<

include make/vesselness-filter-rules.mk
include make/liborion3mat-rules.mk
include make/vaa3d-plugin-rules.mk
