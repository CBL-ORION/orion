## Dependency generation
MAKEDEPEND.c = gcc -MM $(CPPFLAGS) -o $(df.c).d $<
MAKEDEPEND.cc = gcc -MM $(CXXFLAGS) $(CPPFLAGS) -o $(df.cc).d $<
df.c = $(<:%.c=$(DEPDIR)/%)
df.cc = $(<:%.cxx=$(DEPDIR)/%)
MKDIR_DEPEND.c = mkdir -p `dirname $(df.c).d`; $(MAKEDEPEND.c); \
	    $(CP) $(df.c).d $(df.c).P; \
	    sed -e 's/$(HASHMARK).*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	        -e '/^$$/ d' -e 's/$$/ :/' < $(df.c).d >> $(df.c).P; \
	    $(RM) $(df.c).d
MKDIR_DEPEND.cc = mkdir -p `dirname $(df.cc).d`; $(MAKEDEPEND.cc); \
	    $(CP) $(df.cc).d $(df.cc).P; \
	    sed -e 's/$(HASHMARK).*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	        -e '/^$$/ d' -e 's/$$/ :/' < $(df.cc).d >> $(df.cc).P; \
	    $(RM) $(df.cc).d
