//main.ino
// To enable compilation in arduino-cli

#include "main.h"
#include "hardware.h"
#include "utils.h"
#include "../src/main.cpp"
#include "../src/hardware.cpp"
#include "../src/utils.cpp"

int turnNumber = 0;

void setup() {
    hardwareSetup();
}

void loop() {
    Serial.println("looping");
    turnNumber++;
    while (detectDistance() < 100) {
        Serial.print("going inside loop");
        goForward(255, 1000);
        Serial.print("going forwards");
    }
    Serial.println("turning left");
    if (turnNumber % 2 == 0) {
        turnLeft(1000);
    }
    else {
        turnRight(1000);
    }
}