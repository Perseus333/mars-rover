// utils.cpp
// Helper functions

#include "constants.h"
#include "utils.h"
#include <math.h>

float toRadians(short angleInDegrees) {
    float angleInRadians = angleInDegrees * PI_NUM / 180;
    return angleInRadians;
}

// Custom implementation of map() function from `arduino.h`
short map(short value, short initialLow, short initialHigh, short finalLow, short finalHigh) {
    short valueMapped = (short)((finalHigh - finalLow) * ((float)(value - initialLow) / (float)(initialHigh - initialLow)) + finalLow);
    return valueMapped;
}

unsigned short calcDistance(Position pos1, Position pos2) {
    unsigned short distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
    return distance;
}