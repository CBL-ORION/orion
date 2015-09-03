## Tests
C_TAP_HARNESS_PATH := external/c-tap-harness/c-tap-harness

ifdef TEST_VERBOSE
  TEST_VERBOSE_FLAG := -v
else
  TEST_VERBOSE_FLAG :=
endif

#RUNTESTS := $(C_TAP_HARNESS_PATH)/tests/runtest
RUNTESTS := $(C_TAP_HARNESS_PATH)/tests/runtests $(TEST_VERBOSE_FLAG)

TEST_CFLAGS   :=
TEST_CPPFLAGS := -I$(C_TAP_HARNESS_PATH) -I$(C_TAP_HARNESS_PATH)/tests
TEST_LDFLAGS  := -L$(C_TAP_HARNESS_PATH)/tests/tap
TEST_LDLIBS   := -ltap
