/* ******************************************************** */
/* Controle de velocidade e acionamento dos motores do robo */
/* ******************************************************** */

#include "Control.hpp"

encTable actVel = {0, 0};
encTable lastPos = {0, 0};
encTable velSetpoint = {0, 0};

bool controlOn = false;

/* Prototypes */
void timerConfig();
void controlLoop();
void updateActVel();

void controlBegin(int leftPin, int rightPin) {
    controlOn = false;
    timerConfig();

    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);

    delay(10);
    controlOn = true;
}

/* Funcao roda a 10 Hz */
ISR(TIMER1_COMPA_vect) {
    updateActVel();
    controlLoop();
}

void updateActVel() {
    /* Atualiza valores atuais de velocidade */
    actVel.left = abs(actPos.left - lastPos.left);
    actVel.right = abs(actPos.right - lastPos.right);
    lastPos.left = actPos.left;
    lastPos.right = actPos.right;
}

void controlLoop() {
    if (!controlOn) return;
}

void timerConfig() {
    /* set timer1 interrupt at 10 Hz */
    cli();                    // stop interrupts
    TCCR1A = 0;               // set entire TCCR1A register to 0
    TCCR1B = 0;               // same for TCCR1B
    TCNT1 = 0;                // initialize counter value to 0
    OCR1A = 6249;             // = (16*10^6 Hz) / (10 Hz * 256) - 1 (must be < 65536)
    TCCR1B |= (1 << WGM12);   // turn on CTC mode - Clear Timer on Compare
    TCCR1B |= (1 << CS12);    // Set CS12 bit for 256 prescaler
    TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
    sei();                    // allow interrupts
}