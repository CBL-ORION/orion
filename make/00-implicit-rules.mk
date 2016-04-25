### Implict rules
$(BUILDDIR)/%.o : $(LIBDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILD)
	@echo "  [ CC SRC $@ ]"
	$(NOECHO)$(COMPILE.c) -o $@ $<

$(BUILDTESTDIR)/%$(EXEEXT): $(TESTDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BUILDTESTDIR)
	@echo "  [ LINK TEST $@ ]"
	$(NOECHO)$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
ifdef BUILD_GCOV
	# move the .gcno file to the directory with the executable
	mv `basename $@ $(EXEEXT)`.gcno `dirname $@`
endif

$(BUILDTESTDIR)/%$(EXEEXT): $(TESTDIR)/%.cxx
	mkdir -p `dirname $@`
	@echo "  [ LINK TEST $@ ]"
	$(NOECHO)$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(BINDIR)/%$(EXEEXT): $(SRCDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BIN)
	@echo "  [ LINK BINARY $@ ]"
	$(NOECHO)$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
ifdef BUILD_GCOV
	# move the .gcno file to the directory with the executable
	mv `basename $@ $(EXEEXT)`.gcno `dirname $@`
endif

$(BINDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR_DEPEND.c)
	@$(MKDIR_BIN)
	@echo "  [ CC SRC $@ ]"
	$(NOECHO)$(COMPILE.c) -o $@ $<
