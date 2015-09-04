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
GCOVFLAGS :=  -g -O0 -fprofile-arcs -ftest-coverage --coverage -fprofile-dir=$(BUILDDIR)
CMAKEGCOVFLAGS :=

# RELEASEFLAGS, CMAKERELEASEFLAGS: used when neither BUILD_DEBUG nor BUILD_GCOV exist
RELEASEFLAGS :=
CMAKERELEASEFLAGS :=

ifdef BUILD_DEBUG
CFLAGS     += $(DEBUGFLAGS)
LDFLAGS    += $(DEBUGFLAGS)
CMAKEFLAGS += $(CMAKEDEBUGFLAGS)
else ifdef BUILD_GCOV
#CFLAGS     += $(GCOVFLAGS)
LDFLAGS    += $(GCOVFLAGS)
CMAKEFLAGS += $(CMAKEGCOVFLAGS)
else # BUILD_RELEASE
CFLAGS     += $(RELEASEFLAGS)
# add optimisation flags
CFLAGS     += $(CFLAGS.OPT)
LDFLAGS    += $(RELEASEFLAGS)
CMAKEFLAGS += $(CMAKERELEASEFLAGS)
endif

CMAKE := cmake
### Set variables to pass into CMakeLists.txt
CMAKEFLAGS := -D LIBDIR=${FULL_LIBDIR} -D BUILDDIR=${FULL_BUILDDIR}

CMAKE.generate := $(CMAKE) $(CMAKEFLAGS)

GCOV := gcov


include make/dep.mk
