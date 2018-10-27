/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 1 de octubre de 2018, 19:01
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"

#define _XTAL_FREQ 32000000
#define boton PORTDbits.RD2
#define salida LATDbits.LATD1

int seleccion=0; // 0=1Khz 1=100Hz
int precarga1k=64536;
int precarga100=55536; //precarga de 10ms
//int precarga100=45536;// precarga de 50 ms
void __interrupt () interrupcion(void){
    salida=salida+1;
    //__delay_ms(500);
    switch(seleccion){
        case 0:
            TMR1=precarga1k;
            break;
        case 1:
            TMR1=precarga100;
            break;
    }
    PIR4bits.TMR1IF=0; //Limpia bandera de timer 1
     //LIMPIA LA BANDERA
}

int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    //<<<<<<<<<<<<<<<<<<<< PUERTO PARA BOTON Y SALIDA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTD=0;
    ANSELD=0;
    TRISDbits.TRISD2=1; //ENTRADA DEL BOTON
    TRISDbits.TRISD1=0; //SALIDA DE LA SENAL
    
    //>>>>>>>>>>>>>>>>>>>>> Configuracion de interrupciones <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PIR4bits.TMR1IF=0; //Limpia bandera de timer 1
    PIE4bits.TMR1IE=1;//Habilita interrupcion por timer 1
    INTCONbits.GIE=1; //Habilita interrupcion global
    INTCONbits.PEIE=1; // habilita interrupcion por periferico
    PIE4bits.TMR1IE=1;
     //<<<<<<<<<<<<<<<<<<<<<<<<<<<< CONFIGURACION DE TMR1 >>>>>>>>>>>>>>>>>>>>>>>
    T1CONbits.CKPS=0b10; //PREESCALER    
    T1CLKbits.CS=0b0001;//Frecuencia FOCS/4
    T1CONbits.nSYNC=1; //NO SINCRONIZADO
    
    TMR1=precarga1k; // PRECARGA Inicia con la de 1KHz
    T1CONbits.ON=1; //este es el bueno
    //T1CONbits.TMR1ON=1;
    //T1GCONbits.GE=0;
    
    while(1){
        while(boton==0){
            seleccion=1;
           /* salida=salida+1;
            __delay_ms(5);*/
        
        }
        while(boton==1){
            seleccion=0;
            /*salida=salida+1;
            __delay_us(500);*/
        }
    }
    
    
    return (EXIT_SUCCESS);
}

/*          Configuraciones para preescaler
            11 = 1:8 Prescale value
            10 = 1:4 Prescale value
            01 = 1:2 Prescale value
            00 = 1:1 Prescale value
         */
//T1CLKbits.T1CS=0001; //Clock Select bits 0001 = FOSC/4  o 0010 para FOSC