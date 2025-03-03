// Arduino.h
// This is a fake file so that the compiler doesn't complain

#ifndef ARDUINO_H
#define ARDUINO_H

#include <stdint.h>

typedef uint8_t byte;

class FakeSerial {
    public:
        int available() {
            return 0;
        }
        char read() {
            return 'a';
        }
        void print(const char* msg) {
            (void)msg;
        }
        void println(char msg) {
            (void)msg;
        }
        void println(const char* msg) {
            (void)msg;
        }
        void begin(int baud) {
            (void)baud;
        }
};

inline FakeSerial Serial;

inline void pinMode(byte pin, void* output) {
    (void)pin;
    (void)output;
}
inline void digitalWrite(byte pin, void* input) {
    (void)pin;
    (void)input;
}
inline void analogRead(byte pin, void* arg) {
    (void)pin;
    (void)arg;
}
inline void analogWrite(byte pin, int arg) {
    (void)pin;
    (void)arg;
}
inline void delay(char* time) {
    (void)time;
}

extern void* INPUT;
extern void* OUTPUT;
extern void* LOW;
extern void* HIGH;

#endif // ARDUINO_H