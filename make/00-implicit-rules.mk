### Implict rules
$(BUILDDIR)/%.o : $(LIBDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILD)
	$(COMPILE.c) -o $@ $<

$(BUILDTESTDIR)/%$(EXEEXT): $(TESTDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILDTESTDIR)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
ifdef BUILD_GCOV
	# move the .gcno file to the directory with the executable
	mv `basename $@ $(EXEEXT)`.gcno `dirname $@`
endif

$(BUILDTESTDIR)/%$(EXEEXT): $(TESTDIR)/%.cxx
	mkdir -p `dirname $@`
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(BINDIR)/%$(EXEEXT): $(SRCDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BIN)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
ifdef BUILD_GCOV
	# move the .gcno file to the directory with the executable
	mv `basename $@ $(EXEEXT)`.gcno `dirname $@`
endif

$(BINDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BIN)
	$(COMPILE.c) -o $@ $<
