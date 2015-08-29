ITK_CONFIG_MK := make/itk/itk-config.mk.gen
include $(ITK_CONFIG_MK)

$(ITK_CONFIG_MK):  make/itk/CMakeLists.txt
	@$(MKDIR_BUILD)
	$(CMAKE.generate) -B$(BUILDDIR)/.make/itk -Hmake/itk
