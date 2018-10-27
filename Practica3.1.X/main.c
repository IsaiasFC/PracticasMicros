/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 21 de septiembre de 2018, 20:25
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 32000000
#define LED1 LATAbits.LATA2
#define LED2 LATAbits.LATA3

/*IOC interrupt on change 
 *Puede suceder cuando se detecta un flanco de subida o de bajada 
 *Se puede configurar de manera indicidual
 *Se puede confifurar en INTCON
 *IOCxP (Para flancos de subida) Interrut on change positive Edge register
 *IOCxN (Para flancos de bajada)
 *EJP IOCBP= 0b00000001; para B0 como flanco de subida
 *IOCxF registro que tiene las banderas indivuales para cada cambio de estado
 *GIE en registro INTCON para bandera global
 *IOCIE  en registro PIE0
 *IOCE en registro PIR0  
 * 
 */
void __interrupt () interrupcio(void){
    if(IOCBFbits.IOCBF0==1){
        LED1=LED1+1;
        __delay_ms(250);
        IOCBF=0;
    }
    if(IOCAFbits.IOCAF0==1){
        LED2=LED2+1;
        __delay_ms(250);
        IOCAF=0;
    }
    
    /*LATB4=LATB4+1;
    __delay_ms(300);
    PIR0bits.IOCIF=0;//Limpia la bandera general
    IOCAF=0;//Limpia la bandera individual IOC*/
}
int main(int argc, char** argv) {
    //Configuracion del oscilador
    OSCFRQbits.HFFRQ=0b110;
    //puertos
    PORTA=0;
    ANSELA=0;
    TRISA=255;//Como entradas 
    PORTB=0;
    ANSELB=0;
    TRISB=0;//Como salidas
    //PULL UP
    WPUAbits.WPUA0=1;
    //IOC CONFIGURACION
    IOCANbits.IOCAN0=1;//Flanco de bajada en RA0
    IOCAF=0;//Limpia las banderas indicviduales en IOC PORTA
    IOCBPbits.IOCBP0=1;//Flanco de subida en RB0
    IOCBF=0;//Limpia las banderas indicviduales en IOC PORTB
    //////////////////////////////////////////////////////
    if(IOCAFbits.IOCAF0==0){
        LED1=LED1+1;
        IOCAF=0;
    }
    //////////////////////////////////////////////////////
    //Interrupciones
    PIR0bits.IOCIF=0;//LIMPIA BADERA GENERAL IOC
    PIE0bits.IOCIE=1; //Habilita la interrupcion en IOC
    INTCONbits.GIE=1; // Habilita interrupcion global
    
    //ciclo infinito
    while(1);
    return (EXIT_SUCCESS);
}



