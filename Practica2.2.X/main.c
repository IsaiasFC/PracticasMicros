/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 3 de septiembre de 2018, 18:59
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#define boton1 PORTAbits.RA0 //A0
#define led1 LATAbits.LATA6   //A6
#define boton2 PORTBbits.RB0   //B0
#define led2 LATBbits.LATB7     //B7

#define _XTAL_FREQ 32000000

/*
 * 
 */


int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    //Limpiar puertos
    PORTA=0;
    PORTB=0;
    //ANSELAbits.ANSA0=0; SE DEFINE COMO DIGITALRES
    ANSELA=0b00000000;
    ANSELB=0b00000000;
    TRISAbits.TRISA0=1;
    TRISAbits.TRISA6=0;
    TRISBbits.TRISB0=1;
    TRISBbits.TRISB7=0;
    //TRISA=0b00000001;
    //TRISB=0b00000001;
    //WPUA=0b00000001;
    //WPUB=0b00000001;
    
    while(1){
        if(boton1==0){
            __delay_ms(250);
            led1=led1+1;
        }
        if(boton2==0){
            __delay_ms(250);
            led2=led2+1;
        }
    }
    
    return (EXIT_SUCCESS);
}

