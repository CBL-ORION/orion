$(BUILDTESTDIR)/container/array: $(BUILDDIR)/container/array.o $(BUILDDIR)/util/util.o

$(BUILDTESTDIR)/container/vector: $(BUILDDIR)/container/vector.o $(BUILDDIR)/util/util.o

$(BUILDTESTDIR)/orion3-config-parser/parse-file: $(BUILDDIR)/util/util.o $(BUILDDIR)/simple-log/simplelog.o \
	$(BUILDDIR)/param/param.o $(BUILDDIR)/param/orion3.o \
	$(BUILDDIR)/orion3-config-parser/parser.o $(BUILDDIR)/container/array.o


test: $(TEST_OBJ)
	$(RUNTESTS) $(TEST_OBJ)
test: CPPFLAGS += $(TEST_CPPFLAGS)
test: LDFLAGS  += $(TEST_LDFLAGS)
test: LDLIBS   += $(TEST_LDLIBS)
