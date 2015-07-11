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
