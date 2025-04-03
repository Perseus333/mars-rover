// utils.hpp
// Helper functions

#ifndef UTILS_HPP
#define UTILS_HPP

// Change this values by specifying them on the make command
// Fallback for Makefile, usually this values aren't read
#ifndef SCANS_PER_SWIPE
#define SCANS_PER_SWIPE 10 // Increase for more accuracy but lower speeds
#endif

#ifndef MAX_MEMORY
#define MAX_MEMORY 1020 // Affects memory usage
#endif

#ifndef INTIAL_CAPACITY
#define INITIAL_CAPACITY 255 // 2^8-1; max values for 1 byte
#endif

#ifndef DEBUG
#define DEBUG false
#endif

typedef struct DataPacket DataPacket;
typedef struct Position Position;


// ALL DISTANCES IN MILLIMETRES (mm)
struct Position {
    // short allows a radius of 32m of distance representation.
    // The course will be much shorter, and this is half
    // as memory heavy as regular `int`
    short x;
    short y;
};

// ALL ANGLES IN DEGREES (º)
struct DataPacket {
    Position currentPos;
    short vehicleRotation;
    unsigned short obstacleDistance;
    short sensorRotation;
};

// Custom implementation of map function
short map(short value, short initialLow, short initialHigh, short finalLow, short finalHigh);

// Converts angles from degrees to radians
float toRadians(short angleInDegrees);

#endif // UTILS_HPP