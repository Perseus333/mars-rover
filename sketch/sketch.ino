//main.ino
// To enable compilation in arduino-cli

//#include "main.h"
//#include "../src/main.cpp"
#include "hardware.h"
#include "../src/hardware.cpp"
//#include "../src/utils.cpp"

void setup() {
    // mainSetup();
}

void loop() {
    // mainLoop();
    while (detectDistance() > 200) {
        goForward(255, 1000);
    }
    turnLeft(1000);
}