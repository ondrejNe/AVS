
## Project build commands  ------------------------------------------------------------------------
.PHONY: build clean clean-build

build:
	pio run

upload:
ifeq ($(TARGET),)
	eho "Please specify a target to upload"
else
	pio run -e $(TARGET) --target upload
endif

clean:
	pio clean

clean-build: clean build
