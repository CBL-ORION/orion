include make/helper.mk
include make/config.mk

## Source files
BIN_SRC.c   := $(SRCDIR)/segmentation/orion-segmentation.c
BIN_SRC_CONFIG.c   := $(SRCDIR)/config/configurator.c
BIN_SRC.cc  := $(SRCDIR)/compute-filter/ComputeFilter.cxx $(SRCDIR)/subsample-volume/SubsampleVolume.cxx
#LIB_SRC.c  := $(LIBDIR)/ndarray/ndarray3.c  # $(LIBDIR)/filter/hdaf/Makefilter.c
LIB_SRC.c  := $(shell find $(LIBDIR) -path lib/t -prune -o  -type f -name '*.c' \! -name '*_impl.c' -print)
LIB_SRC.cc  := $(shell find $(LIBDIR) \
	-path lib/t -prune -o \
	-path lib/vaa3d-plugin -prune -o \
	-path lib/config -prune -o \
	-path lib/filter/vesselness -prune -o \
	-path lib/integration -prune -o \
	-type f -name '*.cxx' -print)
$(echo $(LIB_SRC.cc))
TEST.c := $(shell find $(TESTDIR) -path lib/t/liborion3mat -prune -o -type f -name "*.c" -print)
ifdef FEAT_LIBORION3MAT
TEST.c  += $(TESTDIR)/liborion3mat/test.c
endif # FEAT_LIBORION3MAT

include make/autodep.mk

## Target files
OBJ_PATHSUBST.c  = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(1))
OBJ_PATHSUBST.cc  = $(patsubst $(LIBDIR)/%.cxx,$(BUILDDIR)/%.o,$(1))
TEST_PATHSUBST.c = $(patsubst $(TESTDIR)/%.c,$(BUILDTESTDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST.c  = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST.cc  = $(patsubst $(SRCDIR)/%.cxx,$(BINDIR)/%$(EXEEXT),$(1))

MKDIR_BUILD.c = mkdir -p `dirname $(call OBJ_PATHSUBST.c,$<)`
MKDIR_BUILD.cc = mkdir -p `dirname $(call OBJ_PATHSUBST.cc,$<)`
MKDIR_BIN   = mkdir -p `dirname $(call BIN_PATHSUBST.c,$<)`
MKDIR_BUILDTESTDIR = mkdir -p `dirname $(call TEST_PATHSUBST.c,$<)`

include make/filter-vesselness-config.mk
include make/vaa3d-plugin-config.mk
include make/test-config.mk
include make/liborion3mat-config.mk
include make/misc-config.mk
include make/liborion-config.mk

## Generate the targets
LIB_OBJ:= $(call OBJ_PATHSUBST.c,$(LIB_SRC.c))
LIB_OBJ+= $(call OBJ_PATHSUBST.cc,$(LIB_SRC.cc))

TEST_OBJ:= $(call TEST_PATHSUBST.c,$(TEST.c))

BIN_BIN.c := $(call BIN_PATHSUBST.c,$(BIN_SRC.c))
BIN_BIN_CONFIG.c := $(call BIN_PATHSUBST.c,$(BIN_SRC_CONFIG.c))
BIN_BIN.cc := $(call BIN_PATHSUBST.cc,$(BIN_SRC.cc))

CONFIG_HEADER_FILE := $(LIBDIR)/config/config.h
$(CONFIG_HEADER_FILE): $(BIN_BIN_CONFIG.c)
	$(BIN_BIN_CONFIG.c) > $@

.PHONY: tags $(DOXYGENDIR)

ifdef PROD
  DEV_TARGETS :=
else
  DEV_TARGETS := tags $(VAA3D_ORION_MATLAB_LIB_OBJ)
endif

## Rules
all: $(CONFIG_HEADER_FILE) $(OUTPUT_DIRS) $(LIBORION.A) $(LIB_OBJ) \
	$(BIN_BIN.c) \
	$(BIN_BIN.cc) \
	$(DEV_TARGETS)

### Output directories
$(OUTPUT_DIRS): # multiple targets
	mkdir -p $@

### Clean
clean:
	-find . -type f -name '*.o' -delete
	-find . -type f \( -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' \) -delete
	-rm -Rf $(OUTPUT_DIRS)
	-rm -Rf $(DOXYGENDIR)
	-rm -Rf $(ITK_CONFIG_MK)
	-rm -Rf $(GCOVDIR) $(LCOVDIR)
	-rm -Rf $(CONFIG_HEADER_FILE)
	-rm -Rf $(LIBORION.A)
	-rm $(VAA3D_ORION_MATLAB_LIB_OBJ)


include make/00-implicit-rules.mk

-include $(LIB_SRC.c:$(LIBDIR)/%.c=$(DEPDIR)/$(LIBDIR)/%.P)
-include $(TEST.c:$(TESTDIR)/%.c=$(DEPDIR)/$(TESTDIR)/%.P)

doc: $(DOXYGENDIR)

$(DOXYGENDIR): make/Doxyfile
	doxygen $<
tags:
	ctags --exclude=external -R .
	# add the ORION 3 code to the tags so that it is easy to jump to the other codebase
	ctags -R -a ${ORION3MAT_PATH}
sloccount:
	sloccount $(LIBDIR)/ $(SRCDIR)/ tool/ make/

dep.liborion3mat:
	mkdir external; git clone https://github.com/CBL-ORION/liborion3mat-mcr-minimal.git external/liborion3mat-mcr-minimal
	mkdir external; git clone https://github.com/CBL-ORION/liborion3mat-deploy.git external/liborion3mat

dep.test-data:
	git clone https://github.com/CBL-ORION/test-data.git test-data

dep.external: dep.external.c-tap-harness dep.external.kiss-fft

dep.external.c-tap-harness:
	./tool/external/c-tap-harness/download && ./tool/external/c-tap-harness/build
dep.external.kiss-fft:
	./tool/external/kiss-fft/download && ./tool/external/kiss-fft/build

include make/filter-vesselness-rules.mk
include make/liborion3mat-rules.mk
include make/vaa3d-plugin-rules.mk
include make/test-rules.mk
include make/util-rules.mk
include make/misc-rules.mk
include make/devops-rules.mk
include make/liborion.mk
