## Tests
C_TAP_HARNESS_PATH := external/c-tap-harness/c-tap-harness

#RUNTESTS := $(C_TAP_HARNESS_PATH)/tests/runtest
RUNTESTS := $(C_TAP_HARNESS_PATH)/tests/runtests

TEST_CPPFLAGS := -I$(C_TAP_HARNESS_PATH) -I$(C_TAP_HARNESS_PATH)/tests
TEST_LDFLAGS  := -L$(C_TAP_HARNESS_PATH)/tests/tap
TEST_LDLIBS   := -ltap

CPPFLAGS := $(CPPFLAGS) $(TEST_CPPFLAGS)
LDFLAGS  := $(LDFLAGS)  $(TEST_LDFLAGS)
LDLIBS   := $(LDLIBS)   $(TEST_LDLIBS)


## Vaa3D
VAA3D_PATH := external/vaa3d/src/v3d_external

FULL_VAA3D_PATH := `cd ${VAA3D_PATH}; pwd`
