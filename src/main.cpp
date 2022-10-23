#include <Arduino.h>

#include "Encoder.hpp"

/* Pinout */
#define ENC_LEFT 2
#define ENC_RIGHT 3

#define ULTRA_LEFT 4
#define ULTRA_MID 4
#define ULTRA_RIGHT 4

void setup() {
    encoderBegin(ENC_LEFT, ENC_RIGHT);
}

void loop() {
}