VTK_CONFIG_MK := make/vtk/vtk-config.mk.gen
include $(VTK_CONFIG_MK)

BIN_VTK_IMAGE_MAPPER := $(BINDIR)/vtk-image-mapper/ImageMapper$(EXEEXT)
TEST_VTK_BUILD: $(BIN_VTK_IMAGE_MAPPER)

$(BIN_VTK_IMAGE_MAPPER): CPPFLAGS += $(VTK_CPPFLAGS)
$(BIN_VTK_IMAGE_MAPPER): LDFLAGS  += $(VTK_LDFLAGS)
$(BIN_VTK_IMAGE_MAPPER): LDLIBS   += $(VTK_LDLIBS)
$(BIN_VTK_IMAGE_MAPPER): make/vtk/ImageMapper.cxx
	mkdir -p `dirname $@`
	@echo "  [ LINK TEST $@ ]"
	$(NOECHO)$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(VTK_CONFIG_MK):  make/vtk/CMakeLists.txt \
		| $(BUILDDIR)
	@$(MKDIR_BUILD)
	$(CMAKE.generate) -B$(BUILDDIR)/.make/vtk -Hmake/vtk
	echo "VTK_LDLIBS += `./tool/script/extract-linker-flags.pl < $(BUILDDIR)/.make/vtk/CMakeFiles/ImageMapper.dir/link.txt`" >> $@

VTK_LDFLAGS += -msse2 -rdynamic
