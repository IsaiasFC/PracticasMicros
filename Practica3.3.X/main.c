/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 27 de septiembre de 2018, 19:30
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#define _XTAL_FREQ 32000000

#define a LATCbits.LATC1
#define b LATCbits.LATC0//**definido
#define c LATCbits.LATC6
#define d LATCbits.LATC5    
#define e LATCbits.LATC4
#define f LATCbits.LATC2
#define g LATDbits.LATD1 //ANTES D3
#define punto LATCbits.LATC7

#define display1 LATAbits.LATA7
#define display2 LATDbits.LATD4
#define display3 LATAbits.LATA6


void numero(int numero){
    switch(numero){
        case 0:
            a=0;b=0;c=0;d=0;e=0;f=0;g=1;punto=1;
            break;
        case 1:
            a=1;b=0;c=0;d=1;e=1;f=1;g=1;punto=1;
            break;
        case 2:
            a=0;b=0;c=1;d=0;e=0;f=1;g=0;punto=1;
            break;
        case 3:
            a=0;b=0;c=0;d=0;e=1;f=1;g=0;punto=1;
            break;
        case 4:
            a=1;b=0;c=0;d=1;e=1;f=0;g=0;punto=1;
            break;
        case 5:
            a=0;b=1;c=0;d=0;e=1;f=0;g=0;punto=1;
            break;
        case 6:
            a=0;b=1;c=0;d=0;e=0;f=0;g=0;punto=1;
            break;
        case 7:
            a=0;b=0;c=0;d=1;e=1;f=1;g=0;punto=1;
            break;
        case 8:
            a=0;b=0;c=0;d=0;e=0;f=0;g=0;punto=1;
            break;
        case 9:
            a=0;b=0;c=0;d=1;e=1;f=0;g=0;punto=1;
            break;
    }
}

void display(int ndisplay){
    switch(ndisplay){
        case 1:
            display1=1; display2=0; display3=0;
            break;
        case 2:
            display1=0; display2=1; display3=0;
            break;
        case 3:
            display1=0; display2=0; display3=1;
            break;
        
    }
}
void retardo(void){
    __delay_ms(8);
}

void getnumeros(int n){
    if(n<10){
     display(1);// mosatra el numero n en el display 1
     numero(n);
     retardo();
     
     display(2);
     numero(0); // display 2 muestra 0
     retardo();
     
     display(3);
     numero(0);// display 3 muestra 0
     retardo();
    }else if(n<100){
        display(1);// mosatra las unidades del numero n en el display 1
        numero(n-((n/10)*10));
        retardo();
        
        display(2); //display 2 muestra las decenas
        numero(n/10);
        retardo();
        
        display(3);
        numero(0);// display 3 muestra las centenas
        retardo();
    }else if(n>=100){
        display(1);// mosatra las unidades del numero n en el display 1
        numero(n-(((n/100)*100)+(((n-((n/100)*100))/10)*10)));
        retardo();
        
        display(2); //display 2 muestra las decenas
        numero((n-((n/100)*100))/10);
        retardo();
        
        display(3);
        numero(n/100);// display 3 muestra las centenas
        retardo();
    }
}
void __interrupt () interrupcion(void){
    
    PIR0bits.TMR0IF=0; //LIMPIA LA BANDERA
}
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    
    //puertos para LEDs de DISPLAY 
    PORTC=0;
    ANSELC=0;
    TRISC=0;
    WPUC=0b11111111;
    //PUERTO PARA BOTON
    PORTB=0;
    ANSELB=0;
    TRISBbits.TRISB7=1;
    //puertos para transistores
    PORTD=0;
    ANSELD=0;
    TRISD=0;
    PORTA=0;
    ANSELA=0;
    TRISA=0;
    //<<<<<<<<<<   CONFIGURACION DE TMR0     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    T0CKIPPSbits.T0CKIPPS=0x0F; //entrada de reloj en RB7    
    T0CON0bits.T016BIT=0; // TMR0 como 8 bits
    T0CON0bits.T0OUTPS=0000; //POSTSCALER 1:1
    T0CON1bits.T0CS=000; // Seleccion de entrada DE RELOJ
    T0CON1bits.T0ASYNC=0; //No esta sincronizado
    T0CON1bits.T0CKPS=0000; //PRESCALER SELECCIONADO 1:1
    TMR0H=250;
    T0CON0bits.T0EN=1; //Habilitar TMR0
    
    //<<<<<<<<<< Configuracion de INTERRUPCIONES >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PIR0bits.TMR0IF=0;//Limpia la bandera
    PIE0bits.TMR0IE=1;//Habilita int Timer0
    INTCONbits.GIE=1; //interrupcion global
    while(1){getnumeros(TMR0L);};
    
    return (EXIT_SUCCESS);
}

