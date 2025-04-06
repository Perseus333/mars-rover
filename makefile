#makefile
#Makes the artifacts

# Compiler and flags
# Compiler: GNU Compiler Collection
CC = g++
# Flags: It should provide all possible waarnings plus good optimization
CFLAGS  = -g -grecord-gcc-switches -O2 -Wall -Wextra -pedantic
CFLAGS += -I./include
CFLAGS += -I./lib/SparkFun_TB6612FNG_Arduino_Library/src
CFLAGS += -I"$(HOME)/AppData/Local/Arduino15/packages/arduino/hardware/avr/**"
CFLAGS += -I./fake

# Adds the math library for trig calculations
LDFLAGS = -lm

# Source files
SRC = src/main.cpp src/hardware.cpp src/utils.cpp lib/SparkFun_TB6612FNG_Arduino_Library/src/SparkFun_TB6612.cpp

#Arguments, default values
SCANS_PER_SWIPE = 10
MAX_MEMORY = 1020
INITIAL_CAPACITY = 255
DEBUG = false

# Specifies the default output when creating the binary
OUT = build/main

# Default target
all: bin arduino

# Build the executable (.exe)
bin: $(OUT)
# You can change the arguments by defining them after `make`. E.g.:
# make SCANS_PER_SWIPE=5 MAX_MEMORY=100 INITIAL_CAPACITY=50
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(OUT) \
	-DSCANS_PER_SWIPE=$(SCANS_PER_SWIPE) \
	-DMAX_MEMORY=$(MAX_MEMORY) \
	-DINITIAL_CAPACITY=$(INITIAL_CAPACITY) \
	-DDEBUG=$(DEBUG)

# Builds the arduino machine code (.hex)
# This can directly be flashed into the arduino without requiring compilation
.PHONY: arduino
arduino:
	arduino-cli compile -b arduino:avr:uno --output-dir build \
	--library lib/SparkFun_TB6612FNG_Arduino_Library \
	--library include \
	sketch/sketch.ino \
	--build-property build.extra_flags="-DSCANS_PER_SWIPE=$(SCANS_PER_SWIPE) -DMAX_MEMORY=$(MAX_MEMORY) -DINITIAL_CAPACITY=$(INITIAL_CAPACITY) -DDEBUG=$(DEBUG)"