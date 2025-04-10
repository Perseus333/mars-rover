//main.ino
// To enable compilation in arduino-cli

#include "main.h"
#include "../src/main.cpp"
#include "hardware.h"
#include "../src/hardware.cpp"
#include "../src/utils.cpp"

int turnNumber = 0;

void setup() {
    // mainSetup();
}

void loop() {
    turnNumber++;
    while (detectDistance() < 100) {
        goForward(255, 10);
    }
    if (turnNumber % 2 == 0) {
        turnLeft(1000);
    }
    else {
        turnRight(1000);
    }
}