# set to empty in order to print commands
NOECHO := @

MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

# unused variables from the default GNU make database: ensure that they are empty
TARGET_ARCH ?=
LOADLIBES ?=
LDLIBS ?=

BLANKMARK :=
HASHMARK = \#
SPACEMARK := $(BLANKMARK) $(BLANKMARK)
TABMARK :=$(BLANKMARK)	$(BLANKMARK)

GUNZIP := gunzip
ZCAT := zcat

%: %.gz
	$(ZCAT) < $< > $@
