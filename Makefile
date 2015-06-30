include config.mk

## Source files
SRC  := $(LIBDIR)/ndarray/ndarray3.c $(LIBDIR)/hdaf-filter/Makefilter.c
TEST := $(TESTDIR)/canary.c $(TESTDIR)/ndarray/ndarray.c

## Dependency generation
df = $(DEPDIR)/$(*)
MAKEDEPEND = gcc -M $(CPPFLAGS) -o $(df).d $<

## Target files
OBJ_PATHSUBST  = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(1))
TEST_PATHSUBST = $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%$(EXEEXT),$(1))

OBJ:= $(call OBJ_PATHSUBST,$(SRC))
#OBJ:= $(patsubst $(LIBDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))

TEST_OBJ:= $(call TEST_PATHSUBST,$(TEST))
#TEST_OBJ:= $(patsubst $(TESTDIR)/%.c,$(BUILDDIR)/%.o,$(TEST))

## Rules
all: $(OUTPUT_DIRS) $(OBJ)

test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)

### Output directories
$(BUILDDIR):
	mkdir -p $@
$(TEST_BUILDDIR):
	mkdir -p $@
$(DEPDIR):
	mkdir -p $@

### Clean
clean:
	find -type f -name '*.o' -delete
	rm -Rf .build/ .deps/

### Implict rules
$(BUILDDIR)/%.o : $(LIBDIR)/%.c
	@mkdir -p `dirname $(df).d`; $(MAKEDEPEND); \
	    cp $(df).d $(df).P; \
	    sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	        -e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P; \
	    rm -f $(df).d
	@mkdir -p `dirname $(call OBJ_PATHSUBST,$<)`
	$(COMPILE.c) -o $@ $<

-include $(SRC:$(LIBDIR)/%.c=$(DEPDIR)/%.P)
