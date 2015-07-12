## liborion3mat
ORION3MAT_PATH := external/orion3mat
# Functions to make available
ORION3MAT_MCC_FUNCTION := ${ORION3MAT_PATH}/main/ORION3.m
# Paths that should be in the ctfroot
ORION3MAT_MCC_ADD_PATH := -a ${ORION3MAT_PATH}

ORION3MAT_LIB_BASE := orion3mat
ORION3MAT_LIB_NAME := lib${ORION3MAT_LIB_BASE}
ORION3MAT_LIB_OBJ_PATH := $(BUILDDIR)/${ORION3MAT_LIB_NAME}
ORION3MAT_LIB_OBJ  := ${ORION3MAT_LIB_OBJ_PATH}/${ORION3MAT_LIB_NAME}.${SO}

# List of MATLAB toolboxes that are needed
#   - Image Processing Toolbox
#   - Curve Fitting Toolbox
#   - Statistics Toolbox
ORION3MAT_MCC_TOOLBOX := -p curvefit -p images -p stats

# Which warnings to enable
ORION3MAT_MCC_WARNING := -w enable:specified_file_mismatch \
	-w enable:repeated_file \
	-w enable:switch_ignored \
	-w enable:missing_lib_sentinel \
	-w enable:demo_license

## liborion3mat flags
LIBORION3MAT_CFLAGS       :=
LIBORION3MAT_CPPFLAGS     := -I${ORION3MAT_LIB_OBJ_PATH}
LIBORION3MAT_LDFLAGS      := -L${ORION3MAT_LIB_OBJ_PATH}
LIBORION3MAT_LDLIBS       := -l${ORION3MAT_LIB_BASE}
