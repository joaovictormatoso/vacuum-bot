#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "DriverLcd.h"
#include "DriverLocomocao.h"
#include "SensorDistancia.h"

#define MIN_DIST 20

#define FRENTE 0
#define AFASTAR 1
#define VIRA1 2
#define VIRA2 3

float dist_esquerda, dist_direita, dist_baixo;
float MAX_DIST;

SensorDistancia sensorDireita(2, 3);
SensorDistancia sensorEsquerda(12, 13);
SensorDistancia sensorFrente(8, 9);
DriverLocomocao motoresLocomocao(5, 6, 10, 11);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(12, INPUT);
    pinMode(13, OUTPUT);
    pinMode(8, INPUT);
    pinMode(9, OUTPUT);
    pinMode(7, INPUT_PULLUP);

    Serial.begin(9600);

    // cli();  // stop interrupts

    // TCCR1A = 0;  // set entire TCCR1A register to 0
    // TCCR1B = 0;  // same for TCCR1B
    // TCNT1 = 0;   // initialize counter value to 0
    // // set compare match register for 1hz increments
    // OCR1A = 15624;  // = (16*10^6) / (1*1024) - 1 (must be <65536)
    // // turn on CTC mode
    // TCCR1B |= (1 << WGM12);
    // // Set CS10 and CS12 bits for 1024 prescaler
    // TCCR1B |= (1 << CS12) | (1 << CS10);
    // // enable timer compare interrupt
    // TIMSK1 |= (1 << OCIE1A);

    // sei();  // start irq

    lcd.init();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Vacuum Robots SA");
    lcd.setCursor(0, 1);
    lcd.print("   Alfredo II   ");

    delay(2000);
    MAX_DIST = sensorFrente.getDistance();
    delay(1000);
    MAX_DIST += sensorFrente.getDistance();
    delay(1000);
    MAX_DIST += sensorFrente.getDistance();
    delay(1000);
    MAX_DIST += sensorFrente.getDistance();
    MAX_DIST = MAX_DIST/4 + 10;

}

int state = FRENTE;

void loop() {
    char line1[17], line2[17];

    if(digitalRead(7)) {
        state=FRENTE;
        motoresLocomocao.parar();
        delay(100);
        return;
    }

    dist_direita = sensorDireita.getDistance();
    dist_esquerda = sensorEsquerda.getDistance();
    dist_baixo = sensorFrente.getDistance();

    switch (state) {
        case FRENTE:
            if (!(dist_direita > MIN_DIST && dist_esquerda > MIN_DIST && dist_baixo < MAX_DIST)) {
                state = AFASTAR;
                break;
            }

            motoresLocomocao.moverFrente();
            break;

        case AFASTAR:
            motoresLocomocao.parar();
            delay(1000);
            motoresLocomocao.moverTras();
            delay(1500);
            motoresLocomocao.parar();
            delay(1000);
            state = VIRA1;
            break;

        case VIRA1:
            motoresLocomocao.virarDireita();
            delay(500);
            state = VIRA2;
            break;

        case VIRA2:
            if (dist_direita > MIN_DIST && dist_esquerda > MIN_DIST && dist_baixo < MAX_DIST) {
                state = FRENTE;
                break;
            }
            motoresLocomocao.virarDireita();
            break;

        default:
            break;
    }

    sprintf(line1, "FR %d", (int)dist_baixo);
    sprintf(line2, "E %d D %d", (int)dist_esquerda, (int)dist_direita);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);

    // Serial.print("Sensor Direita: ");
    // Serial.println(dist_direita);

    // Serial.print("Sensor Esquerda: ");
    // Serial.println(dist_esquerda);

    // Serial.print("Sensor Frente: ");
    // Serial.println(dist_baixo);

    // Serial.println("State");
    // Serial.println(state);

    delay(10);
}

// ISR(TIMER1_COMPA_vect) {
//     dist_direita = sensorDireita.getDistance();
//     Serial.print("Sensor Direita: ");
//     Serial.println(dist_direita);

//     dist_esquerda = sensorEsquerda.getDistance();
//     Serial.print("Sensor Esquerda: ");
//     Serial.println(dist_esquerda);

//     dist_baixo = sensorFrente.getDistance();
//     Serial.print("Sensor Frente: ");
//     Serial.println(dist_baixo);
// }
