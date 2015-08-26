$(BUILDDIR)/param/orion3.o: $(BUILDDIR)/container/array.o
$(BUILDDIR)/container/array.o: $(LIBDIR)/container/array_impl.h $(LIBDIR)/container/array_impl.c
$(BUILDDIR)/param/param.o: $(BUILDDIR)/container/array.o

$(BUILDDIR)/integration/itk/libIntegrationITK.a: $(LIBDIR)/integration/itk/itk.cxx $(FILTER_OBJ)
	@$(MKDIR_BUILD)
	$(CMAKE.generate) -B$(BUILDDIR)/integration/itk -H$(LIBDIR)/integration/itk
	$(MAKE) -C$(BUILDDIR)/integration/itk
