include make/helper.mk
include make/config.mk

## Source files
BIN_SRC  := src/compute-filter/ComputeFilter.cxx
LIB_SRC  := $(LIBDIR)/ndarray/ndarray3.c  # $(LIBDIR)/hdaf-filter/Makefilter.c
TEST := $(TESTDIR)/canary.c $(TESTDIR)/ndarray/ndarray.c

include make/autodep.mk

## Target files
OBJ_PATHSUBST  = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(1))
TEST_PATHSUBST = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST  = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%$(EXEEXT),$(1))

MKDIR_BUILD = mkdir -p `dirname $(call OBJ_PATHSUBST,$<)`
MKDIR_BIN   = mkdir -p `dirname $(call BIN_PATHSUBST,$<)`

LIB_OBJ:= $(call OBJ_PATHSUBST,$(LIB_SRC))

TEST_OBJ:= $(call TEST_PATHSUBST,$(TEST))

include make/vesselness-filter.mk
include make/vaa3d-plugin.mk

## Rules
all: $(OUTPUT_DIRS) $(LIB_OBJ) \
	$(FILTER_OBJ) $(FILTER_BIN) \
	$(ORION_MATLAB_LIB_OBJ)

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)

### Output directories
$(OUTPUT_DIRS): # multiple targets
	mkdir -p $@

### Clean
clean:
	find -type f -name '*.o' -delete
	rm -Rf $(OUTPUT_DIRS)
	rm $(ORION_MATLAB_LIB_OBJ)

### Implict rules
$(BUILDDIR)/%.o : $(LIBDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILD)
	$(COMPILE.c) -o $@ $<

-include $(SRC:$(LIBDIR)/%.c=$(DEPDIR)/%.P)

include make/vesselness-filter-rules.mk
include make/vaa3d-plugin-rules.mk
