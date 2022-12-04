#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "DriverLcd.h"
#include "DriverLocomocao.h"
#include "SensorDistancia.h"

#define MIN_DIST 10
#define MAX_DIST 1000

float dist_esquerda, dist_direita, dist_baixo;

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

    Serial.begin(9600);

    cli();  // stop interrupts

    TCCR1A = 0;  // set entire TCCR1A register to 0
    TCCR1B = 0;  // same for TCCR1B
    TCNT1 = 0;   // initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = 15624;  // = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    sei();  // start irq

    lcd.init();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Vacuum Robots SA");
    lcd.setCursor(0, 1);
    lcd.print("   Alfredo II   ");
}

void loop() {
    motoresLocomocao.moverFrente();
    /*
    if (dist_direita > MIN_DIST && dist_esquerda > MIN_DIST && dist_baixo < MAX_DIST) {
        Serial.println("Move pra frente");
        // lcd.setCursor(0, 0);
        // lcd.print("D %f F %f E %f");
        // lcd.setCursor(0, 1);
        // lcd.print("E %f", dist_esquerda);
        motoresLocomocao.moverFrente();
    } else {
        Serial.println("Para");
        motoresLocomocao.parar();
        delay(100);
        motoresLocomocao.moverTras();
        delay(1000);
        motoresLocomocao.parar();
        delay(100);

        while (!(dist_direita > MIN_DIST && dist_esquerda > MIN_DIST && di st_baixo < MAX_DIST)) {
            Serial.println("Virar direita");
            motoresLocomocao.virarDireita();
        }
    }
*/
    delay(100);
}

ISR(TIMER1_COMPA_vect) {
    dist_direita = sensorDireita.getDistance();
    Serial.print("Sensor Direita: ");
    Serial.println(dist_direita);

    dist_esquerda = sensorEsquerda.getDistance();
    Serial.print("Sensor Esquerda: ");
    Serial.println(dist_esquerda);

    dist_baixo = sensorFrente.getDistance();
    Serial.print("Sensor Frente: ");
    Serial.println(dist_baixo);
}
