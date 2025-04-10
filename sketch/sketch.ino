//main.ino
// To enable compilation in arduino-cli

//#include "main.h"
//#include "../src/main.cpp"
#include "hardware.h"
#include "../src/hardware.cpp"
//#include "../src/utils.cpp"

int count = 0;

void setup() {
    // mainSetup();
}

void loop() {
    count++;
    // mainLoop();
    while (detectDistance() > 200) {
        goForward(100, 10);
    }
    if (count % 2 == 0) {
        turnLeft(1250);
    }
    else {
        turnRight(1250);
    }
}