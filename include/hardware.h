// hardware.h
// Used to include Arduino code in main

#ifndef HARDWARE_H
#define HARDWARE_H

#include <SparkFun_TB6612.h>

int detectDistance();
void swipeScan(short *distanceReport);
void hardwareSetup();
void motorDrive(byte motor, int speed, int duration);
void motorBrake(byte motor);

#endif // HARDWARE_H