FROM ubuntu:latest

# Add timezone info and that we are not interactive
# so that cmake installs without prompts. 
ENV TZ=Europe/Prague
ENV DEBIAN_FRONTEND=noninteractive

# Download Linux support tools
RUN apt-get update && \
    apt-get clean &&  \
    apt-get install -y \
            build-essential \
            git \
            curl \
            wget \
            unzip \
            python3 \
            python3-pip \
            python3-venv
# Download the project toolchain
RUN apt-get install -y \
            make \
            cmake \
            gcc-arm-none-eabi \
            libnewlib-arm-none-eabi \
            libstdc++-arm-none-eabi-newlib
# Install OpenOCD and GDB
RUN apt-get install -y \
            openocd \
            gdb-multiarch

# Create and activate a virtual environment for PlatformIO
RUN python3 -m venv /opt/platformio-venv
ENV PATH="/opt/platformio-venv/bin:$PATH"
# Install PlatformIO within the virtual environment
RUN /opt/platformio-venv/bin/pip3 install platformio

# Clone and setup the RP2040 SDK
RUN git clone --depth 1 https://github.com/raspberrypi/pico-sdk /home/sdk/pico-sdk && \
    cd /home/sdk/pico-sdk && \
    git pull && \
    git submodule update --init
ENV PICO_SDK_PATH=/home/sdk/pico-sdk

# Set the dev directory
WORKDIR /home/dev
