/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 1 de octubre de 2018, 22:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"


#define _XTAL_FREQ 32000000
//#define boton PORTDbits.RD2
#define boton PORTAbits.RA2
#define salida LATAbits.LATA1

int seleccion=0; // 0=1Khz 1=100Hz
int precarga1k=64536;
int precarga100=55536;
void interrupt isr(){
    salida=salida+1;
    switch(seleccion){
        case 0:
            TMR1=precarga1k;
            break;
        case 1:
            TMR1=precarga100;
            break;
    }
    PIR1bits.TMR1IF=0;//Se limpia la bandera
}
int main(int argc, char** argv) {
    OSCCONbits.IRCF=0b1110;
    OSCCONbits.SCS=0b00;
    
    //<<<<<<<<<<<<<<<<<<<< PUERTO PARA BOTON Y SALIDA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTA=0b00000000;
    ANSELA=0b00000000;
    //WPUDbits.WPUD2=1;//PULL-UP ACTIVA PARA EL BOTON
    TRISAbits.TRISA2=1; //ENTRADA DEL BOTON
    
    TRISAbits.TRISA1=0; //SALIDA DE LA SENAL
    //<<<<<<<<<<<<<<<<<<<<< INTERRUPCION >>>>>>>>>>>>>>>>>>>>>>>
    PIE1bits.TMR1IE=1;//habilitación interrupción Timer1
    PIR1bits.TMR1IF=0;//Se limpia bandera de interrupción
    INTCONbits.GIE=1;//habilitación global
    INTCONbits.PEIE=1;//habilitación por periférico
    //<<<<<<<<<<<<<<<<<<<<< configuración Timer1 >>>>>>>>>>>>>>>>>>>
    T1CONbits.T1CKPS=0b10;//divisor 4
    T1CONbits.TMR1CS=0b00;//Fosc/4
    T1CONbits.T1OSCEN=0;//Oscilador LP deshabilitado
    T1CONbits.nT1SYNC=1;//Sin sincronizar
    T1CONbits.TMR1ON=1;//Prende Timer1
    TMR1=precarga1k;
    while(1){
        /*if(boton==0){
            if(seleccion==0){seleccion=1;}
            if(seleccion==1){seleccion=0;}
        //__delay_ms(1);
        }*/
        while(boton==0){seleccion=1;}
        while(boton==1){seleccion=0;}
    }
    return (EXIT_SUCCESS);
}

