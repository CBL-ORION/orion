KISS_FFT_PATH     := external/kiss-fft/kiss-fft
KISS_FFT_CFLAGS   :=
KISS_FFT_CPPFLAGS := -I$(KISS_FFT_PATH) -I$(KISS_FFT_PATH)/tools
KISS_FFT_LDFLAGS  := -L$(KISS_FFT_PATH)/build
KISS_FFT_LDLIBS   :=  -lm $(KISS_FFT_PATH)/build/libkissfft.a
