# Compiler and flags
# Compiler: GNU Compiler Collection
CC = gcc
# Flags: It should provide all possible waarnings plus good optimization
CFLAGS  = -g -grecord-gcc-switches -O2 -Wall -Wextra -pedantic
CFLAGS += -I./include
CFLAGS += -I"~/AppData/Local/Arduino15/packages/arduino/hardware/avr/**"

# Adds the math library for trig calculations
LDFLAGS = -lm

# Source files
SRC = src/main.cpp src/hardware.cpp src/utils.cpp

#Arguments, default values
SCANS_PER_SWIPE = 10
MAX_MEMORY = 1020
INITIAL_CAPACITY = 255
DEBUG = false

# For when testing on a computer without a board
# Fakes importing the arduino functions
TESTING := true
ifeq ($(TESTING), true)
	LDFLAGS += -I./fake
	OUT = build/main_testing.exe
else
	OUT = build/main_arduino
endif

# Default target
all: $(OUT)

# Build the executable
# You can change the arguments by defining them after `make`. E.g.:
# make SCANS_PER_SWIPE=5 MAX_MEMORY=100 INITIAL_CAPACITY=50
$(OUT): $(SRC) | build
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(OUT) -DSCANS_PER_SWIPE=$(SCANS_PER_SWIPE) -DMAX_MEMORY=$(MAX_MEMORY) -DINITIAL_CAPACITY=$(INITIAL_CAPACITY) -DTESTING=$(TESTING) -DDEBUG=$(DEBUG)

build:
	mkdir -p build
