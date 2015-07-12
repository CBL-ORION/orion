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
