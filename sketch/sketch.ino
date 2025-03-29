//main.ino
// To enable compilation in arduino-cli

#include "main.h"
#include "../src/main.cpp"
#include "../src/hardware.cpp"
#include "../src/utils.cpp"

void setup() {
    mainSetup();
}

void loop() {
    mainLoop();
}