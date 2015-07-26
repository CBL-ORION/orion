### Implict rules
$(BUILDDIR)/%.o : $(LIBDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILD)
	$(COMPILE.c) -o $@ $<

$(BUILDTESTDIR)/%$(EXEEXT): $(TESTDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILDTESTDIR)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(BINDIR)/%$(EXEEXT): $(SRCDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BIN)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(BINDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BIN)
	$(COMPILE.c) -o $@ $<
