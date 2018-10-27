/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 15 de octubre de 2018, 21:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000
/*
 * 
 */
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110; //**velocidad del oscilador
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PUERTO
    PORTB=0; //LIMPA
    ANSELB=0; //PUERTO B COMO DIGITAL
    TRISB=255; //PUERTO B COMO ENTRADA
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>PPS
    RB0PPS=0x09; //MODULO CCP1 SALDRA POR RB0
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>TMR2
    T2CLKCON=0b0001;// CS=FOSC/4
    T2CONbits.ON=1; //ENCENDER TIMER2
    T2CONbits.OUTPS=0; //POSTESCALER 1:1
    T2CONbits.CKPS=0b100; //PRESCALER 1:16
    PR2=255; //FRECUENCIA DE 1.95 KHZ
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CCP1
    CCP1CONbits.EN=1; //HABILITA  EL MODULO CCP1
    CCP1CONbits.FMT=0; //ALENEACION A LA DERECHA CCPR1H, L
    CCP1CONbits.MODE=0b1111; //MODO PWM
    CCPTMRS0bits.C1TSEL=0b01; //timer2 CCP1
    TRISB=0;//PUERTO B COMO SALIDA
    return (EXIT_SUCCESS);
}

