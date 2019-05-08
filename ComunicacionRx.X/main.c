/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 11 de octubre de 2018, 13:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000

char dato;//variable para guardar el dato recibido
void __interrupt() isr(void){
    dato=RC1REG;//GUARDAR EL DATO RECIBIDO EN LA VARIABLE DATO
    if(dato==65){LATBbits.LATB0=1;}//encender foco1
    if(dato==66){LATBbits.LATB0=0;}//apagar foco1
    if(dato==67){LATBbits.LATB1=1;}//encender foco2
    if(dato==68){LATBbits.LATB1=0;}//apagar foco2
    PIR3bits.RCIF=0;//limpia bandera 
}
int main(int argc, char** argv) {
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   CONFIGURACION DEL OSCILADOR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    OSCFRQbits.HFFRQ=0b110;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURAION DE LOS PUERTOS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PORTB=0;//Limpiar puerto B
    ANSELB=0; //PUERTO B COMO DIGITAL
    TRISB=0; // PUERTO B COMO SALIDA
    PORTC=0; // LIMPIA PUERTO C
    ANSELC=0; // PUERTO C COMO DIGITAL
    TRISC=0b10000000; //PUERTO C COMO SALIDAS Y RC7 COMO ENTRADA
           
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURAION DEL PPS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //PAGINA 237 TABLA DE VALORES
    RXPPS=0x17;//RX en RC7
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACION PUERTO SERIE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    RC1STAbits.SPEN=1;//Habilitar puerto serie
    TX1STAbits.BRGH=0;// BAJA VELOCIDA LOW SPEED
    TX1STAbits.SYNC=0;// COMUNICACION ASINCRONA
    RC1STAbits.CREN=1;//Recepcion asincrona modo asincrono PAGINA 571 FORMULAS PARA SABER QUE VELOCIDAD ES. TABLA 
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BAUD RATE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    BAUD1CONbits.BRG16=0;//USART timer de 8bits
    SPBRG=51;// 9600 BAUDS
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACION DE INTERRUPCIONES <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PIR3bits.RCIF=0;//limpiar banderas por recePcion USART
    PIE3bits.RCIE=1;// Habilitar la interrupcion por recepcion USART
    INTCONbits.PEIE=1;//Habilitar interrupcion por periferico
    INTCONbits.GIE=1;// HABILITAR INTERRUPCION GLOBAL
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CICLO INFINITO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    while(1){
    
    }
    
    return (EXIT_SUCCESS);
}

