include make/platform.mk
include make/config-dir.mk

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

# DEBUGFLAGS, CMAKEDEBUGFLAGS: used when BUILD_DEBUG variable exists
DEBUGFLAGS := -g
CMAKEDEBUGFLAGS := -DCMAKE_BUILD_TYPE=debug

# GCOVFLAGS: used when BUILD_GCOV variable exists
GCOVFLAGS.PROFILEDIR = -fprofile-dir=`dirname $@`
#GCOVFLAGS.PROFILEDIR =
GCOVFLAGS =  -g -O0 -fprofile-arcs -ftest-coverage --coverage
CMAKEGCOVFLAGS :=

# GPROFFLAGS: used when the BUILD_GPROF variable exists
GPROFFLAGS := -pg
CMAKEGPROFLAGS :=

# RELEASEFLAGS, CMAKERELEASEFLAGS: used when neither BUILD_DEBUG nor BUILD_GCOV exist
RELEASEFLAGS :=
CMAKERELEASEFLAGS :=

ifdef BUILD_GCOV
# using OPT flags when using gcov is not recommended
BUILD_OPT_FLAGS := 0
CFLAGS     += $(GCOVFLAGS)
CXXFLAGS   += $(GCOVFLAGS)
LDFLAGS    += $(GCOVFLAGS) $(GCOVFLAGS.PROFILEDIR)
CMAKEFLAGS += $(CMAKEGCOVFLAGS)
endif

ifdef BUILD_GPROF
CFLAGS     += $(GPROFFLAGS)
CXXFLAGS   += $(GPROFFLAGS)
LDFLAGS    += $(GPROFFLAGS)
CMAKEFLAGS += $(CMAKEGPROFLAGS)
endif

ifdef BUILD_DEBUG
CFLAGS     += $(DEBUGFLAGS)
LDFLAGS    += $(DEBUGFLAGS)
CMAKEFLAGS += $(CMAKEDEBUGFLAGS)
else # BUILD_RELEASE
# set BUILD_OPT_FLAGS only if it has not been unset before
BUILD_OPT_FLAGS ?= 1
CFLAGS     += $(RELEASEFLAGS)
LDFLAGS    += $(RELEASEFLAGS)
CMAKEFLAGS += $(CMAKERELEASEFLAGS)
endif

ifeq ($(BUILD_OPT_FLAGS),1)
# add optimisation flags
CFLAGS     += $(CFLAGS.OPT)
endif


CMAKE := cmake
### Set variables to pass into CMakeLists.txt
CMAKEFLAGS := -D LIBDIR=${FULL_LIBDIR} -D BUILDDIR=${FULL_BUILDDIR}

CMAKE.generate := $(CMAKE) $(CMAKEFLAGS)

GCOV := gcov
GPROF := gprof

include make/dep.mk
