/* ***************************************************************** */
/* File name:        DriverLocomocao.cpp                             */
/* File description: This file contains the functions/methods for    */
/*                   initializing and using the locomotion           */
/* Author name:      Andre Won, Cassio Dezzoti, Totmes Scheffer,     */
/*                   Guilherme Abreu                                 */
/* Creation date:    11out2021                                       */
/* Revision date:    28nov2021                                       */
/* ***************************************************************** */
#include "DriverLocomocao.h"

#define MOTOR1_S   200
#define MOTOR2_S   180

/* ***************************************************************** */
/* Method name:        DriverLocomocao                               */
/* Method description: Declaring a DriverLocomocao class and         */
/*                     initializing it                               */
/* Input params: pino1, pino2, pino3, pino4                          */
/* Output params: n/a                                                */
/* ***************************************************************** */
DriverLocomocao::DriverLocomocao(byte pino1, byte pino2, byte pino3, byte pino4) {
    this->pino1 = pino1;
    this->pino2 = pino2;
    this->pino3 = pino3;
    this->pino4 = pino4;

    void initLocomocao();
}

/* ***************************************************************** */
/* Method name:        initLocomocao                                 */
/* Method description: Initializing Locomotion                       */
/* Input params: n/a                                                 */
/* Output params: n/a                                                */
/* ***************************************************************** */
void DriverLocomocao::initLocomocao() {
    pinMode(pino1, OUTPUT); /* setting pino1 as Output */
    pinMode(pino2, OUTPUT); /* setting pino2 as Output */
    pinMode(pino3, OUTPUT); /* setting pino3 as Output */
    pinMode(pino4, OUTPUT); /* setting pino4 as Output */

    digitalWrite(pino1, LOW); /* setting pino1 as LOW signal */
    digitalWrite(pino2, LOW); /* setting pino2 as LOW signal */
    digitalWrite(pino3, LOW); /* setting pino3 as LOW signal */
    digitalWrite(pino4, LOW); /* setting pino4 as LOW signal */
}

/* ***************************************************************** */
/* Method name:        moverFrente                                   */
/* Method description: Moving robot forward                          */
/* Input params: n/a                                                 */
/* Output params: n/a                                                */
/* ***************************************************************** */
boolean DriverLocomocao::moverFrente() {
    // toda velocidade
    analogWrite(pino1, 0);   /* setting pino2 as 0 on an analog level */
    analogWrite(pino2, MOTOR1_S); /* setting pino1 as 240 on an analog level */
    analogWrite(pino3, 0);   /* setting pino4 as 0 on an analog level */
    analogWrite(pino4, MOTOR2_S); /* setting pino3 as 210 on an analog level */
    // falta a parte do encoder
    return false;
}

/* ***************************************************************** */
/* Method name:        moverTras                                     */
/* Method description: Moving robot backwards                        */
/* Input params: n/a                                                 */
/* Output params: n/a                                                */
/* ***************************************************************** */
boolean DriverLocomocao::moverTras() {
    analogWrite(pino1, MOTOR1_S*0.8); /* setting pino2 as 240 on an analog level */
    analogWrite(pino2, 0);   /* setting pino1 as 0 on an analog level */
    analogWrite(pino3, MOTOR2_S*0.8); /* setting pino4 as 210 on an analog level */
    analogWrite(pino4, 0);   /* setting pino3 as 0 on an analog level */

    return false;
}

/* ***************************************************************** */
/* Method name:        parar                                         */
/* Method description: stop the robot from moving                    */
/* Input params: n/a                                                 */
/* Output params: n/a                                                */
/* ***************************************************************** */
void DriverLocomocao::parar() {
    digitalWrite(pino1, LOW); /* setting pino1 as LOW signal */
    digitalWrite(pino2, LOW); /* setting pino2 as LOW signal */
    digitalWrite(pino3, LOW); /* setting pino3 as LOW signal */
    digitalWrite(pino4, LOW); /* setting pino4 as LOW signal */
}

/* ***************************************************************** */
/* Method name:        virarDireita                                  */
/* Method description: Turn robot to the right                       */
/* Input params: n/a                                                 */
/* Output params: true or false                                      */
/* ***************************************************************** */
boolean DriverLocomocao::virarDireita() {
    analogWrite(pino1, 0);   /* setting pino 1 as 0 on an analog level */
    analogWrite(pino2, 0);   /* setting pino 2 as 0 on an analog level */
    analogWrite(pino3, 0);   /* setting pino 4 as 0 on an analog level */
    analogWrite(pino4, MOTOR2_S); /* setting pino 3 as 210 on an analog level */
    return false;
}

/* ***************************************************************** */
/* Method name:        virarEsquerda                                 */
/* Method description: Turn robot to the left                        */
/* Input params: n/a                                                 */
/* Output params:  true or false                                     */
/* ***************************************************************** */
boolean DriverLocomocao::virarEsquerda() {
    analogWrite(pino1, 0);   /* setting pino 2 as 0 on an analog level */
    analogWrite(pino2, MOTOR1_S); /* setting pino 1 as 240 on an analog level */
    analogWrite(pino3, 0);   /* setting pino 3 as 0 on an analog level */
    analogWrite(pino4, 0);   /* setting pino 4 as 0 on an analog level */
    return false;
}
