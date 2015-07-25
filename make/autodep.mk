## Dependency generation
df = $(DEPDIR)/$(*)
MAKEDEPEND.c = gcc -M $(CPPFLAGS) -o $(df).d $<
MKDIR_DEPEND.c = mkdir -p `dirname $(df).d`; $(MAKEDEPEND.c); \
	    $(CP) $(df).d $(df).P; \
	    sed -e 's/$(HASHMARK).*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	        -e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P; \
	    $(RM) $(df).d