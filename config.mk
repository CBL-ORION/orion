CPPFLAGS := -Ilib
CFLAGS   := -std=c11
LDFLAGS  := -lm

## Directories
BUILDDIR := .build
LIBDIR   := lib
TESTDIR  := lib/t
DEPDIR   := .deps
OUTPUT_DIRS := $(BUILDDIR) $(DEPDIR)

include dep.mk
include platform.mk
