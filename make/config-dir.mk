## Directories
SRCDIR   := src

# output of ${SRCDIR}
BINDIR   := bin

LIBDIR   := lib
TESTDIR  := lib/t

# output of ${LIBDIR} and ${TESTDIR}
BUILDDIR := .build
BUILDTESTDIR := $(BUILDDIR)/t

# output used to build deps information for make(1)
DEPDIR   := .deps

OUTPUT_DIRS := $(BUILDDIR) $(BUILDTESTDIR) $(DEPDIR) $(BINDIR)

FULL_LIBDIR := `cd ${LIBDIR}; pwd`
FULL_BUILDDIR := `cd ${BUILDDIR}; pwd`

GCOVDIR := report-gcov
LCOVDIR := report-lcov
