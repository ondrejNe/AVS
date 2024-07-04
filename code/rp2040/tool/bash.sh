#!/bin/bash

# Check if the firmware file argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <firmware_file>"
    exit 1
fi

# Define the serial port and firmware file path
SERIAL_PORT="/dev/cu.usbmodem1101"
FIRMWARE_PATH="/Users/necasond/Library/Arduino15/packages/arduino/tools/rp2040tools/1.0.6/rp2040load"
FIRMWARE_FILE="$1"

# Reset the microcontroller by opening the serial port at 1200 bps and closing it
echo "Performing 1200-bps touch reset on ${SERIAL_PORT}..."
stty -f $SERIAL_PORT 1200
sleep 2 # Wait a bit for the device to reset

# Run the firmware loader
echo "Running firmware loader..."
$FIRMWARE_PATH -v -D "$FIRMWARE_FILE"

echo "Firmware loading complete."
