PARALLEL	:= 1

## Project build commands  ------------------------------------------------------------------------
.PHONY: all build flash clean clean-build
all: build

build:
	mkdir -p build
	cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -S ./ -B build
	cmake --build build --parallel $(PARALLEL)

flash: build
	@echo "Starting flash process..."
	@if [ -z "$(TARGET)" ]; then \
		echo "Error: TARGET is not set"; \
		exit 1; \
	fi
	@echo "TARGET is set to $(TARGET). Searching for the corresponding ELF file..."
	@# Search for the ELF file
	$(eval ELF_FILE := $(shell find build -name '$(TARGET).elf' -print -quit))
	@# Print the found ELF file
	@if [ -z "$(ELF_FILE)" ]; then \
		echo "Error: No ELF file found matching $(TARGET).elf"; \
		exit 1; \
	fi
	@echo "ELF file located at: $(ELF_FILE)"
	@# Execute the OpenOCD command to flash the firmware
	@echo "Flashing $(ELF_FILE) using OpenOCD..."
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(ELF_FILE) verify reset exit"
	@echo "Flashing completed successfully."

clean:
	rm -rf build cmake-build-debug

clean-build: clean build
