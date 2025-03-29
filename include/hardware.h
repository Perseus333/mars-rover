// hardware.h
// Used to include Arduino code in main

#ifndef HARDWARE_H
#define HARDWARE_H

int detectDistance();
void swipeScan(short *distanceReport);
void hardwareSetup();

#endif // HARDWARE_H