#export C_INCLUDE_PATH=/home/beau/Downloads/L3.0.101_4.1.1_141016_source/gpu-viv-bin-mx6q-3.0.101-4.1.1/usr/include
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CCLIBS += -framework OpenCL
else
	CCLIBS += -lOpenCL -lm -lGAL -ldl
	CFLAGS += -std=gnu99
endif

SOURCE_C_FILES = main.c

all:	opencl_device_query

opencl_device_query: $(SOURCE_C_FILES)
	$(CC) $(SOURCE_C_FILES) $(CFLAGS) -o opencl_device_query $(CCLIBS) 

clean:
	rm opencl_device_query

