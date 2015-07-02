vaa3d-plugin-orion-matlab: ${ORION_MATLAB_LIB_OBJ}

$(ORION_MATLAB_LIB_OBJ): ${ORION_MATLAB_LIB_SRC_PATH}/orion_matlab_plugin.cpp
	mkdir -p $(ORION_MATLAB_LIB_BUILD_PATH)
	qmake  -makefile -o $(ORION_MATLAB_LIB_BUILD_PATH)/Makefile VAA3DPATH=${VAA3D_PATH} $(ORION_MATLAB_LIB_SRC_PATH)/orion_matlab.pro
	$(MAKE) -C$(ORION_MATLAB_LIB_BUILD_PATH)
