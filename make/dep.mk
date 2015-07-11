## Tests
C_TAP_HARNESS_PATH := external/c-tap-harness/c-tap-harness

#RUNTESTS := $(C_TAP_HARNESS_PATH)/tests/runtest
RUNTESTS := $(C_TAP_HARNESS_PATH)/tests/runtests

TEST_CPPFLAGS := -I$(C_TAP_HARNESS_PATH) -I$(C_TAP_HARNESS_PATH)/tests
TEST_LDFLAGS  := -L$(C_TAP_HARNESS_PATH)/tests/tap
TEST_LDLIBS   := -ltap

    ### Add TAP harness to existing flags
define ADD_PACKAGE_TEST
CPPFLAGS += $(TEST_CPPFLAGS)
LDFLAGS  += $(TEST_LDFLAGS)
LDLIBS   += $(TEST_LDLIBS)
endef


## Vaa3D
VAA3D_PATH := external/vaa3d/src/v3d_external

FULL_VAA3D_PATH := `cd ${VAA3D_PATH}; pwd`

## liborion3mat
ORION3MAT_PATH := external/orion3mat
# MATLAB install R2013a (v8.1)
# The value of ${MATLAB} can be obtained by running:
#     mex -v 2>/dev/null | grep "MATLAB *="
MATLAB   := /usr/local/MATLAB/R2013a
# MATLAB Compiler Runtime (v8.1)
MCR := /usr/local/MATLAB/MATLAB_Compiler_Runtime/v81

MATLAB_LD_PRELOAD := /lib/x86_64-linux-gnu/libgcc_s.so.1${PATHSEP}/usr/lib/x86_64-linux-gnu/libstdc++.so.6
MCR_LD_PRELOAD := ${MATLAB_LD_PRELOAD}

MCR_CPPFLAGS := -I${MCR}/extern/include
MCR_CFLAGS   := -fPIC -ansi -D_GNU_SOURCE -DUNIX -DX11 -pthread
MCR_LDFLAGS  := -Wl,-rpath-link,${MCR}/bin/glnxa64 -L${MCR}/runtime/glnxa64 -pthread
MCR_LDLIBS   := -lmwmclmcrrt -lm

MATLAB_LD_LIBRARY_PATH := ${MATLAB}/bin/glnxa64${PATHSEP}${MATLAB}/runtime/glnxa64
MCR_LD_LIBRARY_PATH := ${MCR}/runtime/glnxa64${PATHSEP}${MCR}/bin/glnxa64${PATHSEP}${MCR}/sys/os/glnxa64${PATHSEP}${MCR}/sys/java/jre/glnxa64/jre/lib/amd64/native_threads${PATHSEP}${MCR}/sys/java/jre/glnxa64/jre/lib/amd64/server${PATHSEP}${MCR}/sys/java/jre/glnxa64/jre/lib/amd64
XAPPLRESDIR := ${MCR}/X11/app-defaults

    ### Add MCR to existing flags
define ADD_PACKAGE_MCR
    CFLAGS   += ${MCR_CFLAGS}
    CPPFLAGS += ${MCR_CPPFLAGS}
    LDFLAGS  += ${MCR_LDFLAGS}
    LDLIBS   += ${MCR_LDLIBS}
endef


