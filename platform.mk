UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	EXEEXT :=
else
	EXEEXT := .exe
endif
