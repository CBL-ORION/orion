$(BUILDDIR)/param/orion3.o: $(BUILDDIR)/container/array.o
$(BUILDDIR)/container/array.o: $(LIBDIR)/container/array_impl.h $(LIBDIR)/container/array_impl.c
$(BUILDDIR)/param/param.o: $(BUILDDIR)/container/array.o

