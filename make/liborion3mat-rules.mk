# NOTE: only need to keep: liborion3mat.so liborion3mat.h readme.txt
#
# Have to cd to make sure that the CTF archive is clean. Otherwise it will
# contain the full path.
${ORION3MAT_LIB_OBJ}: ${ORION3MAT_PATH}/${ORION3MAT_MCC_FUNCTION}
	if [ -d external/${ORION3MAT_LIB_NAME}  ]; then \
		cp -puvr external/${ORION3MAT_LIB_NAME} ${ORION3MAT_LIB_OBJ_PATH}; \
	else \
		mkdir -p `dirname $@`; \
		export MATLAB_PREFDIR="/tmp/empty-matlab-pref"; \
		cd ${ORION3MAT_PATH}; \
		mcc \
			-W lib:${ORION3MAT_LIB_NAME} \
			-T link:lib \
			-d ${FULL_ORION3MAT_LIB_OBJ_PATH} \
			-N \
			${ORION3MAT_MCC_TOOLBOX} \
			${ORION3MAT_MCC_WARNING} \
			-v \
			${ORION3MAT_MCC_FUNCTION} \
			${ORION3MAT_MCC_ADD_PATH}; \
		perl -pi -e 's|/.*orion/|orion/|g' ${FULL_ORION3MAT_LIB_OBJ_PATH}/liborion3mat.[ch]; \
	fi
