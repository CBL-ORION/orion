include make/platform.mk
include make/config-dir.mk

# initialise CXXFLAGS
CXXFLAGS :=

# need to point to the headers under the $(LIBDIR)/ directory
CPPFLAGS += -I$(LIBDIR)

# all the C code needs to support C99
CFLAGS   += -std=c99

# enable all warnings
#CFLAGS   += -Wall

#CFLAGS   := -std=c11

# link to the the mathematical functions
LDLIBS   += -lm $(CPPFLAGS)
#LDFLAGS  += $(CPPFLAGS)

# CMAKEFLAGS: flags added to cmake calls
CMAKEFLAGS +=

# AddressSanitizer (ASAN) flags
CFLAGS.ASAN   += -fsanitize=address

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

# RELEASEFLAGS, CMAKERELEASEFLAGS: used when BUILD_DEBUG does not exist
RELEASEFLAGS :=
CMAKERELEASEFLAGS :=

# gcov builds
ifdef BUILD_GCOV
# using OPT flags when using gcov is not recommended
BUILD_ENABLE_OPT := 0
CFLAGS     += $(GCOVFLAGS)
CXXFLAGS   += $(GCOVFLAGS)
LDFLAGS    += $(GCOVFLAGS) $(GCOVFLAGS.PROFILEDIR)
CMAKEFLAGS += $(CMAKEGCOVFLAGS)
endif

# gprof builds
ifdef BUILD_GPROF
CFLAGS     += $(GPROFFLAGS)
CXXFLAGS   += $(GPROFFLAGS)
LDFLAGS    += $(GPROFFLAGS)
CMAKEFLAGS += $(CMAKEGPROFLAGS)
endif


# DEBUG or RELEASE builds
ifdef BUILD_DEBUG
BUILD_ENABLE_ASAN ?= 1

CFLAGS     += $(DEBUGFLAGS)
CXXFLAGS   += $(DEBUGFLAGS)
LDFLAGS    += $(DEBUGFLAGS)
CMAKEFLAGS += $(CMAKEDEBUGFLAGS)
else # BUILD_RELEASE
# set BUILD_ENABLE_OPT only if it has not been unset before
BUILD_ENABLE_OPT ?= 1
BUILD_ENABLE_ASAN ?= 1

CFLAGS     += $(RELEASEFLAGS)
CXXFLAGS   += $(RELEASEFLAGS)
LDFLAGS    += $(RELEASEFLAGS)
CMAKEFLAGS += $(CMAKERELEASEFLAGS)
endif


ifeq ($(BUILD_ENABLE_OPT),1)
# add optimisation flags
CFLAGS     += $(CFLAGS.OPT)
endif

# enable AddressSantizer (ASAN)
ifeq ($(BUILD_ENABLE_ASAN),1)
CFLAGS     += $(CFLAGS.ASAN)
endif


CMAKE := cmake
### Set variables to pass into CMakeLists.txt
CMAKEFLAGS += -D CMAKE_CXX_FLAGS:STRING+="$(CXXFLAGS)" -D LIBDIR=${FULL_LIBDIR} -D BUILDDIR=${FULL_BUILDDIR}
## Set the output of the the CMake-generated Makefiles to show all commands
CMAKEFLAGS += -DCMAKE_VERBOSE_MAKEFILE=ON

CMAKE.generate = $(CMAKE) $(CMAKEFLAGS)

GCOV := gcov
GPROF := gprof

include make/dep.mk
