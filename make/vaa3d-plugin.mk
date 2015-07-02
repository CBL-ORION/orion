## Targets

# if this is changed, then the DESTDIR variable in lib/vaa3d-plugin/orion-matlab/orion_matlab.pro
# must also be changed
ORION_MATLAB_LIB_OBJ_DIR := ${VAA3D_PATH}/bin/plugins/bigneuronhackathon/orion_matlab

ORION_MATLAB_LIB_OBJ := $(ORION_MATLAB_LIB_OBJ_DIR)/liborion_matlab.so
ORION_MATLAB_LIB_SRC_PATH := $(LIBDIR)/vaa3d-plugin/orion-matlab
ORION_MATLAB_LIB_BUILD_PATH := $(BUILDDIR)/vaa3d-plugin/orion-matlab
