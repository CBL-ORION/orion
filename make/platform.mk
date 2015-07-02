UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	EXEEXT :=
	CP := cp
else
	EXEEXT := .exe
	CP := copy
endif
