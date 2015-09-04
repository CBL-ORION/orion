include make/helper.mk
include make/config.mk

## Source files
BIN_SRC.c   := $(SRCDIR)/segmentation/orion-segmentation.c
BIN_SRC.cc  := $(SRCDIR)/compute-filter/ComputeFilter.cxx $(SRCDIR)/subsample-volume/SubsampleVolume.cxx
LIB_SRC.c  := $(LIBDIR)/ndarray/ndarray3.c  # $(LIBDIR)/filter/hdaf/Makefilter.c
TEST.c := $(shell find $(TESTDIR) -path lib/t/liborion3mat -prune -o -type f -name "*.c" -print)
ifdef FEAT_LIBORION3MAT
TEST.c  += $(TESTDIR)/liborion3mat/test.c
endif # FEAT_LIBORION3MAT

include make/autodep.mk

## Target files
OBJ_PATHSUBST.c  = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(1))
TEST_PATHSUBST.c = $(patsubst $(TESTDIR)/%.c,$(BUILDTESTDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST.c  = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST.cc  = $(patsubst $(SRCDIR)/%.cxx,$(BINDIR)/%$(EXEEXT),$(1))

MKDIR_BUILD = mkdir -p `dirname $(call OBJ_PATHSUBST.c,$<)`
MKDIR_BIN   = mkdir -p `dirname $(call BIN_PATHSUBST.c,$<)`
MKDIR_BUILDTESTDIR = mkdir -p `dirname $(call TEST_PATHSUBST.c,$<)`

include make/filter-vesselness-config.mk
include make/vaa3d-plugin-config.mk
include make/test-config.mk
include make/liborion3mat-config.mk

## Generate the targets
LIB_OBJ:= $(call OBJ_PATHSUBST.c,$(LIB_SRC.c))

TEST_OBJ:= $(call TEST_PATHSUBST.c,$(TEST.c))

BIN_BIN.c := $(call BIN_PATHSUBST.c,$(BIN_SRC.c))
BIN_BIN.cc := $(call BIN_PATHSUBST.cc,$(BIN_SRC.cc))

.PHONY: tags

ifdef PROD
  DEV_TARGETS :=
else
  DEV_TARGETS := tags $(VAA3D_ORION_MATLAB_LIB_OBJ)
endif

## Rules
all: $(OUTPUT_DIRS) $(LIB_OBJ) \
	$(BIN_BIN.c) \
	$(BIN_BIN.cc) \
	$(DEV_TARGETS) \
	$(BUILDDIR)/integration/itk/libIntegrationITK.a

### Output directories
$(OUTPUT_DIRS): # multiple targets
	mkdir -p $@

### Clean
clean:
	-find . -type f -name '*.o' -delete
	-find . -type f \( -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' \) -delete
	-rm -Rf $(OUTPUT_DIRS)
	-rm -Rf $(ITK_CONFIG_MK)
	-rm $(VAA3D_ORION_MATLAB_LIB_OBJ)

test.build_gcov:
	$(MAKE) test BUILD_GCOV=1
	gcov --preserve-paths

include make/00-implicit-rules.mk

-include $(SRC:$(LIBDIR)/%.c=$(DEPDIR)/%.P)

tags:
	ctags --exclude=external -R .
	# add the ORION 3 code to the tags so that it is easy to jump to the other codebase
	ctags -R -a ${ORION3MAT_PATH}

include make/filter-vesselness-rules.mk
include make/liborion3mat-rules.mk
include make/vaa3d-plugin-rules.mk
include make/test-rules.mk
include make/ndarray-rules.mk
include make/util-rules.mk
include make/misc-rules.mk
