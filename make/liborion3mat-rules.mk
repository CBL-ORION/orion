ifdef FEAT_LIBORION3MAT

# NOTE: only need to keep: liborion3mat.so liborion3mat.h readme.txt
#
# Have to cd to make sure that the CTF archive is clean. Otherwise it will
# contain the full path.
${ORION3MAT_LIB_OBJ}: # ${ORION3MAT_PATH}/${ORION3MAT_MCC_FUNCTION}
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

$(BUILDTESTDIR)/liborion3mat/test: ${ORION3MAT_LIB_OBJ}
$(BUILDTESTDIR)/liborion3mat/test: CFLAGS   += $(LIBORION3MAT_CFLAGS)   $(MCR_CFLAGS)
$(BUILDTESTDIR)/liborion3mat/test: CPPFLAGS += $(LIBORION3MAT_CPPFLAGS) $(MCR_CPPFLAGS)
$(BUILDTESTDIR)/liborion3mat/test: LDFLAGS  += $(LIBORION3MAT_LDFLAGS)  $(MCR_LDFLAGS)
$(BUILDTESTDIR)/liborion3mat/test: LDLIBS   += $(LIBORION3MAT_LDLIBS)   $(MCR_LDLIBS)

.PHONY: liborion3mat.run.with-matlab-env liborion3mat.run.with-mcr-env

# add the MCR to the LD_LIBRARY_PATH
test: LD_PRELOAD := ${MCR_LD_PRELOAD}:${LD_PRELOAD}
test: LD_LIBRARY_PATH := ${ORION3MAT_LIB_OBJ_PATH}:${MCR_LD_LIBRARY_PATH}:${LD_LIBRARY_PATH}

liborion3mat.run.with-matlab-env: $(BUILDTESTDIR)/liborion3mat/test $(TEST_DATA_NPF023)
	# Running using MATLAB for loading dynamic libraries
	LD_PRELOAD=${MATLAB_LD_PRELOAD} LD_LIBRARY_PATH=${ORION3MAT_LIB_OBJ_PATH}:${MATLAB_LD_LIBRARY_PATH} $<
liborion3mat.run.with-mcr-env: $(BUILDTESTDIR)/liborion3mat/test $(TEST_DATA_NPF023)
	# Running using MATLAB Compiler Runtime for loading dynamic libraries
	LD_PRELOAD=${MCR_LD_PRELOAD} LD_LIBRARY_PATH=${ORION3MAT_LIB_OBJ_PATH}:${MCR_LD_LIBRARY_PATH} $<

endif # FEAT_LIBORION3MAT
