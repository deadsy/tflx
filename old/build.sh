#!/bin/bash

XTOOLS="/opt/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi"
TOOL_PATH=$XTOOLS/bin

make -C ./tfl \
BUILD_OPTIONS=cmsis_nn \
CXX=$TOOL_PATH/arm-none-eabi-g++ \
CC=$TOOL_PATH/arm-none-eabi-gcc \
AR=$TOOL_PATH/arm-none-eabi-ar

