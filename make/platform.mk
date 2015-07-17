TEST_DIR_EXIST = $(if $(wildcard $(1)/.),TRUE,FALSE)
# EXEEXT: extension for executables (includes the .)
# SO: extension for shared objects (does not include the .)
ifdef COMSPEC
	# Windows
	EXEEXT := .exe
	PATHSEP := ;
	SO := dll
	CP := copy
else
	EXEEXT :=
	PATHSEP := :
	SO := so
	CP := cp
endif
