//main.cpp
// The main file for the rover

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* `stdint.h` should be replaced with `arduino.h`
As it's only purpose is to use the uint8_t datatype
which arduino already replaces with `byte`
*/
#include <stdint.h>

// Include the custom libraries (header files)
#include "utils.h"
#include "constants.h"
#include "hardware.h"

/*
Integer Data Types
Efficient memory management is crucial in microcontrollers

0 to 255: byte (1 byte)
0 to 64000: unsigned short (2 bytes)
-32000 to 32000: short (2 bytes)
angles and rotations: short (2 bytes)
*/

// Initializing global variables
Position currentPos;
Position* obstacles;
unsigned short obstacleAmount;
short vehicleRotation;
short sensorRotation;
unsigned short obstacleCapacity;
// Sets all the elements in the grid as . for better visibility
char grid[mapSideLength][mapSideLength] = {'.'};

short* scanEnvironment() {
    static short distanceReport[SCANS_PER_SWIPE];
    swipeScan(distanceReport);
    
    return distanceReport;
}

Position generateObstacle(DataPacket data) {

    short overallRotation = data.sensorRotation + data.vehicleRotation;
    short xDistance = (short)(cos(toRadians(overallRotation)) * data.obstacleDistance);
    short yDistance = (short)(sin(toRadians(overallRotation)) * data.obstacleDistance);
    
    Position obstaclePos;
    obstaclePos.x = xDistance + data.currentPos.x;
    obstaclePos.y = yDistance + data.currentPos.y;

    return obstaclePos;
}

void appendObstacle(Position obstacle) {
    // If we need more space, we assign another bit (double it) for the `obstacles` list
    if (obstacleAmount >= obstacleCapacity && obstacleCapacity < MAX_MEMORY) {

        // Only doubles the memory if it it won't exceed the `MAX_MEMORY`
        if (obstacleCapacity*2 < MAX_MEMORY) {
            obstacleCapacity *= 2;
        }
        // The memory that we need to reallocate is that of the size of the struct of Position
        // times the amount of elements that we have in the array
        // the size of Position should be 4 bytes (2 shorts; 2 bytes each) * obstacleCapacity
        Position* temp = (Position*)realloc(obstacles, obstacleCapacity * sizeof(Position));
        if (!temp) {
            printf("Couldn't allocate memory");
            // Blink arduino LED rapidly or something to signal that there is an error
        } 
        // Only update the obstacles if there hasn't been an error with the memory
        else {
            obstacles = temp;
        }
    }
    
    // Replaces old objects instead of overflowing
    obstacleAmount = obstacleAmount % obstacleCapacity;

    obstacles[obstacleAmount].x = obstacle.x;
    obstacles[obstacleAmount].y = obstacle.y;

    obstacleAmount++;
}

// Updates the obstacle map with the obstacles that were detected
void updateObstacleDisplay(short updateAmount) {

    for (int newObstacle = 0; newObstacle < updateAmount; newObstacle++) {
        short mappedX = map(obstacles[newObstacle].x, -32766, 32766, 0, mapSideLength - 1);
        short mappedY = map(obstacles[newObstacle].y, -32766, 32766, 0, mapSideLength - 1);

        if ((mappedX >= 0) && (mappedX < mapSideLength) && (mappedY >= 0) && (mappedY < mapSideLength)) {
            grid[mappedY][mappedX] = '#';
        }
    }

    //      initial value, min initial,   max initial, min target, max target 
    grid[map(currentPos.y, MIN_SHORT_NUM, MAX_SHORT_NUM, 0,    mapSideLength - 1)]
        [map(currentPos.x, MIN_SHORT_NUM, MAX_SHORT_NUM, 0,    mapSideLength - 1)] = 'X';

    // Prints the characters in the terminal
    for (int y = 0; y < mapSideLength; y++) {
        for (int x = 0; x < mapSideLength; x++) {
            putchar(grid[y][x]);
            putchar('.');
        }
        putchar('\n');
    }
}

void updateObstacleMap(short* scanReport) {
    short updateAmount = sizeof(scanReport);
    
    for (short index = 0; index < updateAmount; index++) {
        DataPacket data;
        data.obstacleDistance = scanReport[index];
        data.sensorRotation = sensorRotation;
        data.vehicleRotation = vehicleRotation;
        data.currentPos = currentPos;
        Position obstaclePos = generateObstacle(data);
        appendObstacle(obstaclePos);
    }
    updateObstacleDisplay(SCANS_PER_SWIPE);
}

void turnRight() {
    motorBrake(1); // stops the right motor
    motorDrive(2, 255, 1); // moves the left motor
    delay (1);
}

void turnLeft() {
    motorBrake(2); // stops the left motor
    motorDrive(1, 255, 1); // moves the right motor
    delay (1);
}

void pivot(Position nearestObstacle) {
    uint8_t obstacleAvoided = 0;
    short verticalDistance = nearestObstacle.y - currentPos.y;
    // This means a right turn
    if (verticalDistance > 0) {
        while (obstacleAvoided == 0) {
            turnRight();
            // Once the obstacle is on the other side of the rover
            // it means that it has completed it
            if (nearestObstacle.y - currentPos.y < 0) {
                obstacleAvoided = 1;
            }
            // else continue the while loop
        }
    }
    // Requires a left turn otherwise
    if (verticalDistance < 0) {
        while (obstacleAvoided == 0) {
            turnLeft();
            // Once the obstacle is on the other side of the rover
            // it means that it has completed it
            if (nearestObstacle.y - currentPos.y > 0) {
                obstacleAvoided = 1;
            }
        }
    }
    else {
        // Faulty reading - avoid crash, don't pivot
    }
}

// Selects which is the most optimal route
void pathFind() {
    // Safe guard mechanism
    for (int obstacleIndex = 0; obstacleIndex < obstacleAmount; obstacleIndex++) {
        Position obstacle = obstacles[obstacleIndex];
        // gets the pythagorean distance to the obstacle
        unsigned short distanceToObstacle = calcDistance(obstacle, currentPos);
        if (distanceToObstacle < MAX_SAFE_DISTANCE) {
            // Stops both motors
            motorBrake(1);
            motorBrake(2);

            // Checks if it needs to pivot around a cone
            // all cones are always in line with the
            short horizontal_distance = obstacle.x - currentPos.x;
            if (horizontal_distance < MAX_SAFE_DISTANCE) {
                pivot(obstacle);
            }
        }
        else {
            // Drive forward for a small section of time
            motorDrive(1, 255, 1);
            motorDrive(2, 255, 1);
        }
    }
}

// The setup function in arduino
void mainSetup() {
    // Initializing global variables
    Position currentPos = {0, 0};
    Position* obstacles = NULL;
    unsigned short obstacleAmount = 0;
    short vehicleRotation = 0;
    short sensorRotation = 0;
    unsigned short obstacleCapacity = INITIAL_CAPACITY;
    
    // Allocate memory for obstacles
    obstacles = (Position*)malloc(INITIAL_CAPACITY * sizeof(Position));
}

// The loop function in arduino
void mainLoop() {
    updateObstacleMap(scanEnvironment());
    pathFind();
}

// The `main()` function, is excluded when building to Arduino,
// it's just here for testing/debugging purposes
int main() {

    mainSetup();

    // same as `while true`, but without having to include stdbool.h (more memory efficient)
    for (;;) {
        mainLoop();
    }
    
    return 0;
}