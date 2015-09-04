include make/platform.mk

# need to point to the headers under the lib/ directory
CPPFLAGS += -Ilib

# all the C code needs to support C99
CFLAGS   += -std=c99

# enable AddressSantizer (ASAN)
CFLAGS   += -fsanitize=address

# enable all warnings
#CFLAGS   += -Wall

#CFLAGS   := -std=c11

# link to the the mathematical functions
LDFLAGS  += -lm $(CPPFLAGS)

# CMAKEFLAGS: flags added to cmake calls
CMAKEFLAGS +=

# optimisation flags
CFLAGS.OPT := -O2

# DEBUGFLAGS, CMAKEDEBUGFLAGS: used when DEBUG variable exists
DEBUGFLAGS := -g
CMAKEDEBUGFLAGS := -DCMAKE_BUILD_TYPE=debug

# GCOVFLAGS: used when GCOV variable exists
GCOVFLAGS :=  -g -O0 -fprofile-arcs -ftest-coverage
CMAKEGCOVFLAGS :=

# RELEASEFLAGS, CMAKERELEASEFLAGS: used when neither DEBUG nor GCOV exist
RELEASEFLAGS :=
CMAKERELEASEFLAGS :=

ifdef DEBUG
CFLAGS     += $(DEBUGFLAGS)
LDFLAGS    += $(DEBUGFLAGS)
CMAKEFLAGS += $(CMAKEDEBUGFLAGS)
else ifdef GCOV
CFLAGS     += $(GCOVFLAGS)
LDFLAGS    += $(GCOVFLAGS)
CMAKEFLAGS += $(CMAKEGCOVFLAGS)
else # RELEASE
CFLAGS     += $(RELEASEFLAGS)
# add optimisation flags
CFLAGS     += $(CFLAGS.OPT)
LDFLAGS    += $(RELEASEFLAGS)
CMAKEFLAGS += $(CMAKERELEASEFLAGS)
endif

CMAKE := cmake
CMAKE.generate = $(CMAKE) $(CMAKEFLAGS)

## Directories
SRCDIR   := src

# output of ${SRCDIR}
BINDIR   := bin

LIBDIR   := lib
TESTDIR  := lib/t

# output of ${LIBDIR} and ${TESTDIR}
BUILDDIR := .build
BUILDTESTDIR := $(BUILDDIR)/t

# output used to build deps information for make(1)
DEPDIR   := .deps

OUTPUT_DIRS := $(BUILDDIR) $(DEPDIR) $(BINDIR)

FULL_LIBDIR := `cd ${LIBDIR}; pwd`
FULL_BUILDDIR := `cd ${BUILDDIR}; pwd`

### Set variables to pass into CMakeLists.txt
CMAKEFLAGS := -D LIBDIR=${FULL_LIBDIR} -D BUILDDIR=${FULL_BUILDDIR}

include make/dep.mk
