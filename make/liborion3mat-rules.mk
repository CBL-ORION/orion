# NOTE: only need to keep: liborion3mat.so liborion3mat.h readme.txt
${ORION3MAT_LIB_OBJ}: ${ORION3MAT_MCC_FUNCTION}
	if [ -d external/${ORION3MAT_LIB_NAME}  ]; then \
		cp -puvr external/${ORION3MAT_LIB_NAME} ${ORION3MAT_LIB_OBJ_PATH}; \
	else \
		mkdir -p `dirname $@`; \
		mcc \
			-W lib:${ORION3MAT_LIB_NAME} \
			-T link:lib \
			-d $(BUILDDIR)/liborion3mat \
			-N \
			${ORION3MAT_MCC_TOOLBOX} \
			${ORION3MAT_MCC_WARNING} \
			-v \
			${ORION3MAT_MCC_FUNCTION} \
			${ORION3MAT_MCC_ADD_PATH}; \
	fi
