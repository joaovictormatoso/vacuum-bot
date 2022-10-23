#include "Encoder.hpp"

encTable actPos = {0, 0};
encTable signal = {1, 1};
encTable lastChange = {0, 0};

void encoderBegin(int leftPin, int rightPin) {
    pinMode(leftPin, INPUT);
    pinMode(rightPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(leftPin), enc_leftEncIRQ, CHANGE);
    attachInterrupt(digitalPinToInterrupt(rightPin), enc_rightEncIRQ, CHANGE);
}

void enc_leftEncIRQ() {
    /* Evita bouncing back do sinal */
    if ((micros() - lastChange.left) < ENC_DEADTIME) return;
    lastChange.left = micros();

    /* Verifica se variavel vai explodir e inverte contagem */
    if (actPos.left == 0xFFFFFFFF)
        signal.left = -1;
    else if (actPos.left == 0)
        signal.left = 1;

    /* Atualiza posicao */
    actPos.left += signal.left;
}

void enc_rightEncIRQ() {
    /* Evita bounceback do sinal */
    if ((micros() - lastChange.right) < ENC_DEADTIME) return;
    lastChange.right = micros();

    /* Verifica se variavel vai explodir e inverte contagem */
    if (actPos.right == 0xFFFFFFFF)
        signal.right = -1;
    else if (actPos.right == 0)
        signal.right = 1;

    /* Atualiza posicao */
    actPos.right += signal.right;
}
