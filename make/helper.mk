MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

BLANKMARK :=
HASHMARK = \#
SPACEMARK := $(BLANKMARK) $(BLANKMARK)
TABMARK :=$(BLANKMARK)	$(BLANKMARK)

GUNZIP := gunzip

%: %.gz
	$(GUNZIP) -k $<
