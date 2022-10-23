#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

#define ENC_DEADTIME 50  // Deadtime in microsseconds

typedef struct {
    unsigned long left;
    unsigned long right;
} encTable;

extern encTable actPos;

void encoderBegin(int leftPin, int rightPin);
void enc_leftEncIRQ();
void enc_rightEncIRQ();

#endif