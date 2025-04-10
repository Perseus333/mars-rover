// hardware.h
// Used to include Arduino code in main

#ifndef HARDWARE_H
#define HARDWARE_H

#include <SparkFun_TB6612.h>
// Fires the ultrasonic sensor once at it's current position and returns the distance in milimiters
int detectDistance();
// Swipes the servo whilst doing reads with he ultrasonic sensor
// Reports the data by modifying an array of dinstances
void swipeScan(short *distanceReport);
// The setup process for the hardware components
void hardwareSetup();
// Drives a specific motor, at a certain speed during some miliseconds
void motorDrive(byte motor, int speed, int duration);
// Brakes the specified motor
void motorBrake(byte motor);
// Moves the rover forward
void goForward(int speed, int duration);
// Turns the rover right
void turnRight(int duration);
// Turns the rover left
void turnLeft(int duration);

#endif // HARDWARE_H