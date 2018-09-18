/* 
 * File:   Main.c
 * Author: drasf
 *
 * Created on 3 de septiembre de 2018, 14:39
 */

#include <stdio.h>
#include <stdlib.h>

//incluir las configuraciones
#include "config.h"
#include <xc.h>

//VALOR DE LA FRECUENCIA A 32 Mhz
#define _XTAL_FREQ 32000000
//#define D2 LATDbits.LATD2

/*
 * 
 */
int main(int argc, char** argv) {

    //selecion de la frecuencia deseada 32Mhz
    OSCFRQbits.HFFRQ=0b110; //Selecciona el camino de la frecuencia en los multiplexores
    PORTD=0;// limpia el puerto D
    ANSELD=0b00000000; // Puerto D como digital
    TRISD=0b00000000; //Puerto D como salidas
    
    
    while(1){
        LATDbits.LATD3=LATDbits.LATD3+1;
        //retardo en ms(milis), us(microssegundos))
        __delay_ms(500); //Retardo 500ms
    }
    
    
    
    return (EXIT_SUCCESS);
}

void prender(){

}

