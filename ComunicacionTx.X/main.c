

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 32000000
/*
 * 
 */
int x;
int main(int argc, char** argv) {
    //OSCILADOR
    OSCFRQbits.HFFRQ=0b110;
    //PUERTOS
    
    //ANSELC=0; //PUERTO COMO DIGITAL
    TRISCbits.TRISC7=1; //PUERTO C COMO SALIDA
    PORTC=0; //LIMPIA PUERTO C
    //PPS
    //RC6PPS=0X10; //TX EN C6
    //PUERTO SERIE
    TX1STAbits.SYNC=0; //NO SINCRONIZADO
    TX1STAbits.TXEN=1; //Habilita la transmicion
    RC1STAbits.ADDEN=1;//habilita puerto serie
    //>>>>>>>>>>>>>>>>>>>>>BAUDRATE
    BAUD1CONbits.BRG16=1; //timer BRG como 8 bits
    TX1STAbits.BRGH=1; //BAJA VELOCIDAD 
    SPBRG=832; // ES LO MISMO QUE SPBRGH=51>>8; Y SPBRGL=51;
    //BAUD RATE //es un timer que puede ser de 8 o 16 bits 0 y 1 respecivamente
    
                //>>>>>>>>>>>>>>>>pagina 571 del datasheet para ver las formulas para calcular el baud rate
    
    //DISPOSITIVOS EN PROTEUS COMPIM SOLO EN PROTEUS RX CON RX
    //TERMINAL VIRTUAL Y COMPIM
    //incluri libreria string
    // para obtener longitudes de vectores strlen(string);
    //usar variables unsigned char
    while(1){
      for(x=65;x<=91;x++){
          TX1REG=x;
          while(TX1STAbits.TRMT==0);
          __delay_ms(200);
      }      
    }
    
    
    return (EXIT_SUCCESS);
}

