// hardware.cpp
// Functions related to physical components

#include <Arduino.h>
#include <Servo.h>
#include "utils.h"
#include "constants.h"
#include <SparkFun_TB6612.h>


// You can paste the code below this into the arduino setup and it will work right off the bat

// Defining the pins
// The pins are based on ../assets/board_ref.jpg
// F: forwards; B: backwards

const int PWMB = 9;
const int BIN1 = 8;
const int BIN2 = 10;

const int PWMA = 3;
const int AIN1 = 2;
const int AIN2 = 4;
const int STBY = 12;

const byte TRIG = 6;
const byte ECHO = 5;

const byte SERVO_PIN = 11;

// Modify this values as needed from testing
const byte offsetA = 1;
const byte offsetB = 1;

// Defining the motors
// right motor
Motor motorA = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
// left motor
Motor motorB = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

unsigned short obstacleDistance;

// Configures the servo
Servo sensorServo;

int detectDistance() {
	long duration;
	int distance;

	// Trigger
	digitalWrite(TRIG, LOW);
	digitalWrite(TRIG, HIGH);
	// Defines the signal duration
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);
	
	// Waits for input in the ECHO pin
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

	// Sets trigger pins for sensor
	pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

	

	// Initializes the Serial Monitor (terminal)
	Serial.begin(9600);

	sensorServo.attach(SERVO_PIN);
}

void motorDrive(byte motor, int speed, int duration) {
	Motor selectedMotor = motorA;
    if (motor == 2) {
        selectedMotor = motorB; 
    }
	selectedMotor.drive(speed, duration);
}

void motorBrake(byte motor) {
	Motor selectedMotor = motorA;
    if (motor == 2) {
        selectedMotor = motorB; 
    }
	selectedMotor.brake();
}

void goForward(int speed, int duration) {
	forward(motorA, motorB, 255);
	delay(duration);
	motorBrake(1);
	motorBrake(2);
}

void turnRight(int duration) {
	motorDrive(2, 255, duration);
}

void turnLeft(int duration) {
	motorDrive(1, 255, duration);
}

void brakeMotors() {
	brake(motorA, motorB);
}