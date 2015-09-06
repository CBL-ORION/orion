ITK_CONFIG_MK := make/itk/itk-config.mk.gen
include $(ITK_CONFIG_MK)

$(ITK_CONFIG_MK):  make/itk/CMakeLists.txt \
		| $(BUILDDIR)
	@$(MKDIR_BUILD)
	$(CMAKE.generate) -B$(BUILDDIR)/.make/itk -Hmake/itk
	echo "ITK_LDLIBS += `./tool/script/extract-linker-flags.pl < $(BUILDDIR)/.make/itk/CMakeFiles/Pi.dir/link.txt`" >> $@

ITK_LDFLAGS += -msse2 -rdynamic
