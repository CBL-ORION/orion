vaa3d-plugin-orion-matlab: ${ORION_MATLAB_LIB_OBJ}

$(ORION_MATLAB_LIB_OBJ): ${ORION_MATLAB_LIB_SRC_PATH}/orion_matlab_plugin.cpp
	qmake  -makefile -o $(BUILDDIR)/Makefile.orion-matlab VAA3DPATH=${VAA3D_PATH} $(ORION_MATLAB_LIB_SRC_PATH)/orion_matlab.pro
	cd $(BUILDDIR) && $(MAKE) -f Makefile.orion-matlab
