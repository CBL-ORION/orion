include config.mk

HASHMARK = \#

## Source files
SRC  := $(LIBDIR)/ndarray/ndarray3.c $(LIBDIR)/hdaf-filter/Makefilter.c
TEST := $(TESTDIR)/canary.c $(TESTDIR)/ndarray/ndarray.c

## Dependency generation
df = $(DEPDIR)/$(*)
MAKEDEPEND.c = gcc -M $(CPPFLAGS) -o $(df).d $<
MKDIR_DEPEND.c = mkdir -p `dirname $(df).d`; $(MAKEDEPEND.c); \
	    $(CP) $(df).d $(df).P; \
	    sed -e 's/$(HASHMARK).*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	        -e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P; \
	    $(RM) $(df).d

## Target files
OBJ_PATHSUBST  = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(1))
TEST_PATHSUBST = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%$(EXEEXT),$(1))

MKDIR_BUILD = mkdir -p `dirname $(call OBJ_PATHSUBST,$<)`


OBJ:= $(call OBJ_PATHSUBST,$(SRC))
#OBJ:= $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))

TEST_OBJ:= $(call TEST_PATHSUBST,$(TEST))
#TEST_OBJ:= $(patsubst $(TESTDIR)/%.c,$(BUILDDIR)/%.o,$(TEST))

## Rules
all: $(OUTPUT_DIRS) $(OBJ)

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)

### Output directories
$(OUTPUT_DIRS): # multiple targets
	mkdir -p $@

### Clean
clean:
	find -type f -name '*.o' -delete
	rm -Rf .build/ .deps/

### Implict rules
$(BUILDDIR)/%.o : $(LIBDIR)/%.c
	$(MKDIR_DEPEND.c)
	$(MKDIR_BUILD)
	$(COMPILE.c) -o $@ $<

-include $(SRC:$(LIBDIR)/%.c=$(DEPDIR)/%.P)
