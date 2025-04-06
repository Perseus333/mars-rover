//main.ino
// To enable compilation in arduino-cli

//#include "main.h"
//#include "../src/main.cpp"
#include "hardware.h"
#include "../src/hardware.cpp"
//#include "../src/utils.cpp"

void setup() {
    // mainSetup();
    motorDrive(1, 255, 1000);
    motorDrive(2, 255, 1000);
}

void loop() {
    // mainLoop();
    motorDrive(1, 255, 1000);
    motorDrive(2, 255, 1000);
}