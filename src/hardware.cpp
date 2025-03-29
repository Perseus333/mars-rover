// hardware.cpp
// Functions related to physical components

#include <Arduino.h>
#include <Servo.h>
#include "utils.h"
#include "constants.h"


// You can paste the code below this into the arduino setup and it will work right off the bat

// hardware.cpp
// Functions related to physical components

// You can paste the code below this into the arduino setup and it will work right off the bat

// Defining the pins
// The pins are based on ../assets/board_ref.jpg
// F: forwards; B: backwards
const byte ENABLE_RIGHT = 3;
const byte RIGHT_B = 4;
const byte RIGHT_F = 2;

const byte ENABLE_LEFT = 9;
const byte LEFT_B = 8;
const byte LEFT_F = 10;

const byte RIGHT_LED = 12;
const byte LEFT_LED = 13;

const byte TRIG = 6;
const byte ECHO = 5;

const byte SERVO_PIN = 11;

unsigned short obstacleDistance;

// Configures the servo
Servo sensorServo;

int detectDistance() {
	long duration;
	int distance;

	// Trigger
	digitalWrite(TRIG, LOW);
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);

	duration = pulseIn(ECHO, HIGH);

	distance = duration * SPEED_OF_SOUND / 2;

	// To avoid interferences from previous waves
	delay(1);

	return distance;
}

// Does a full swipe
// The sensor will be mounted on the servo
void swipeScan(short *distanceReport) {
    // Angles are in degrees (0-360º)
    const short ANGLE_STEP = FULL_ROTATION / SCANS_PER_SWIPE;
	// Start always at 0 degrees
	sensorServo.write(0);

    for (uint8_t i = 1; i <= SCANS_PER_SWIPE; i++) {
        short obstacleDistance = detectDistance();
		distanceReport[i] = obstacleDistance;

		if (DEBUG) {
			// Prints the distance to the obstacle;
			Serial.print(obstacleDistance);
			Serial.print(", ");
			// on the last one, print new line
			if (i == SCANS_PER_SWIPE - 1) Serial.println("");
		}
		// Delay between scans just in case
		delay(10);
		short sensorRotation = ANGLE_STEP * i;
		sensorServo.write(sensorRotation);
    }
}

// setup and loop functions are only for demonstrative purposes

void hardwareSetup() {
  
	// Define all DC Motor pins as OUTPUT
	pinMode(ENABLE_RIGHT, OUTPUT);
	pinMode(RIGHT_B, OUTPUT);
	pinMode(RIGHT_F, OUTPUT);
	pinMode(ENABLE_LEFT, OUTPUT);
	pinMode(LEFT_B, OUTPUT);
	pinMode(LEFT_F, OUTPUT);

	// Set all motors off at the beginning
	digitalWrite(RIGHT_B, LOW);
	digitalWrite(RIGHT_F, LOW);
	digitalWrite(LEFT_B, LOW);
	digitalWrite(LEFT_F, LOW);

	// Sets trigger pins for sensor
	pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

	// Always max speed
	analogWrite(ENABLE_LEFT, 255);
	analogWrite(ENABLE_RIGHT, 255);

	// Initializes the Serial Monitor (terminal)
	Serial.begin(9600);

	sensorServo.attach(SERVO_PIN);

}