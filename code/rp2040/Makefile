PARALLEL	:= 1
BIN_SUFFIX 	:= .elf

## Project build commands  ------------------------------------------------------------------------
.PHONY: all build debug clean clean-build clean-debug
all:
	mkdir -p build

build: all
	cmake -S ./ -B ./build/
	cmake --build ./build --parallel $(PARALLEL)
	cp -f ./build/src/**/*$(BIN_SUFFIX) ./src/

upload:
ifeq ($(TARGET),)
	eho "Please specify a target to upload"
else
	sh ./tool/bash.sh $(TARGET)
endif

clean:
	rm -rf build

clean-build: clean build
