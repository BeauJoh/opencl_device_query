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

