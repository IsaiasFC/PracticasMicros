/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 27 de agosto de 2018, 15:26
 */

//#include <stdio.h>
//#include <stdlib.h>
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000
/*
 * 
 */
void main(void) {
    //Configuración del Oscilador
    //OSCCON1bits.NOSC=0b110;
    // OSCCON1bits.NDIV=0b000;
    OSCFRQbits.HFFRQ=0b101; //Selecciona la frecuencia de 16MHz del INTOSC
    //Configuración de puertos
    PORTB=0;    //Limpia puerto B
    TRISB=0;    //Puerto B como salidas
    ANSELB=0;   //Puerto B como digital
 
//4. Inicia ciclo infinito
    while(1){
        LATBbits.LATB7=~LATBbits.LATB7;  //Toggle bits RB0
        __delay_ms(1000);                //Espera 1 segundo
    }
    return ;
}

