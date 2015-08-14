include make/helper.mk
include make/config.mk

## Source files
BIN_SRC.c   := $(SRCDIR)/segmentation/orion-segmentation.c
BIN_SRC.cc  := # $(SRCDIR)/compute-filter/ComputeFilter.cxx $(SRCDIR)/subsample-volume/SubsampleVolume.cxx
LIB_SRC.c  := $(LIBDIR)/ndarray/ndarray3.c  # $(LIBDIR)/hdaf-filter/Makefilter.c
TEST.c := $(TESTDIR)/canary.c $(TESTDIR)/ndarray/ndarray.c $(TESTDIR)/liborion3mat/test.c $(TESTDIR)/container/array.c

include make/autodep.mk

## Target files
OBJ_PATHSUBST.c  = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(1))
TEST_PATHSUBST.c = $(patsubst $(TESTDIR)/%.c,$(BUILDTESTDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST.c  = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%$(EXEEXT),$(1))
BIN_PATHSUBST.cc  = $(patsubst $(SRCDIR)/%.cxx,$(BINDIR)/%$(EXEEXT),$(1))

MKDIR_BUILD = mkdir -p `dirname $(call OBJ_PATHSUBST.c,$<)`
MKDIR_BIN   = mkdir -p `dirname $(call BIN_PATHSUBST.c,$<)`
MKDIR_BUILDTESTDIR = mkdir -p `dirname $(call TEST_PATHSUBST.c,$<)`

LIB_OBJ:= $(call OBJ_PATHSUBST.c,$(LIB_SRC.c))

TEST_OBJ:= $(call TEST_PATHSUBST.c,$(TEST.c))

BIN_BIN.c := $(call BIN_PATHSUBST.c,$(BIN_SRC.c))
BIN_BIN.cc := $(call BIN_PATHSUBST.cc,$(BIN_SRC.cc))

include make/vesselness-filter-config.mk
include make/vaa3d-plugin-config.mk
include make/liborion3mat-config.mk

.PHONY: tags

## Rules
all: $(OUTPUT_DIRS) $(LIB_OBJ) \
	$(BIN_BIN.c) \
	$(BIN_BIN.cc) \
	$(VAA3D_ORION_MATLAB_LIB_OBJ) \
	tags

### Output directories
$(OUTPUT_DIRS): # multiple targets
	mkdir -p $@

### Clean
clean:
	-find . -type f -name '*.o' -delete
	-rm -Rf $(OUTPUT_DIRS)
	-rm $(VAA3D_ORION_MATLAB_LIB_OBJ)

include make/00-implicit-rules.mk

$(BUILDDIR)/container/array.o: $(LIBDIR)/container/array_impl.h $(LIBDIR)/container/array_impl.c

$(BUILDDIR)/param/param.o: $(BUILDDIR)/container/array.o

$(BINDIR)/segmentation/orion-segmentation$(EXEEXT): $(SRCDIR)/segmentation/orion-segmentation.c \
		$(BUILDDIR)/simple-log/simplelog.o $(BUILDDIR)/util.o \
		$(BUILDDIR)/param/segmentation.o $(BUILDDIR)/param/io.o \
		$(BUILDDIR)/param/param.o \
		$(BUILDDIR)/container/array.o

-include $(SRC:$(LIBDIR)/%.c=$(DEPDIR)/%.P)

tags:
	ctags --exclude=external -R .

include make/vesselness-filter-rules.mk
include make/liborion3mat-rules.mk
include make/vaa3d-plugin-rules.mk
include make/test-rules.mk
include make/ndarray-rules.mk
include make/util-rules.mk
