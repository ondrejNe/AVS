PARALLEL	:= 1

## Project build commands  ------------------------------------------------------------------------
.PHONY: all build flash clean clean-build
all:
	mkdir -p build

build: all
	cmake -DCMAKE_TOOLCHAIN_FILE=gcc.cmake -S ./ -B build
	cmake --build ./build --parallel $(PARALLEL)

flash:
	cmake --build build --target flash

clean:
	rm -rf build
	rm -rf cmake-build-debug

clean-build: clean build
