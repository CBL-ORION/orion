$(LIBORION.A): $(LIB_OBJ) $(ITK_INTEGRATION_OBJ)
	mkdir -p `dirname $@`
	$(AR) $(ARFLAGS) $@ $^
