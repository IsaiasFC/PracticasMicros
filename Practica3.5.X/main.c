/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 2 de octubre de 2018, 22:20
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"
#define trig LATAbits.LATA0
#define echo PORTAbits.RA1

int ctiempo=0;
int precarga=65534;// entrar a la interrupcion cada 0.5us
float distancia=0;
int realizar=1;
void __interrupt () interrupcion(void){
    if(echo==0){
        if(ctiempo!=0){distancia=(ctiempo/2)/(29.2);}
        realizar=1;
        ctiempo=0;
       //__delay_ms(100);    
       
    }else{
        ctiempo=ctiempo+1; 
    }
    TMR1=precarga; // PRECARGA 
    PIR4bits.TMR1IF=0; //Limpia bandera de timer 1
     //LIMPIA LA BANDERA
}
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PUERTOS PARA LCD >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
    PORTC=0;
    PORTD=0;
    ANSELC=0b00000000;
    ANSELD=0b00000000;
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< puertos para sensor >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTA=0;
    ANSELA=0;
    TRISAbits.TRISA0=0; //salida
    TRISAbits.TRISA1=1; //entrada
    //>>>>>>>>>>>>>>>>>>>>> Configuracion de interrupciones <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PIR4bits.TMR1IF=0; //Limpia bandera de timer 1
    PIE4bits.TMR1IE=1;//Habilita interrupcion por timer 1
    INTCONbits.GIE=1; //Habilita interrupcion global
    INTCONbits.PEIE=1; // habilita interrupcion por periferico
    PIE4bits.TMR1IE=1;
     //<<<<<<<<<<<<<<<<<<<<<<<<<<<< CONFIGURACION DE TMR1 >>>>>>>>>>>>>>>>>>>>>>>
    T1CONbits.CKPS=0b10; //PREESCALER    
    T1CLKbits.CS=0b0001;//Frecuencia FOCS/4=0001 // EN ESTA PRACTICA EVENTOS EXTERNOS 0000
    T1CONbits.nSYNC=1; //NO SINCRONIZADO
    TMR1=precarga; // PRECARGA 
    //T1GCONbits.GE=0;
    T1CONbits.ON=1; //Inicia el TMR1 
    //<<<<<<<<<<<<<<<<<<<<<<<<< Iniciar LCD >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    unsigned char buffer1[16];
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    
    while(1){
        /*
            trig=0;
            __delay_us(4);  
            trig=1;
            __delay_us(10);
            trig=0;
            
        while(echo){
        T1CONbits.ON=1; //Inicia el TMR1
        TMR1H=0;              
        TMR1L=0;              
        T1CONbits.nSYNC=1; //NO SINCRONIZADO
        }
        distancia=TMR1L;*/
        //>>>>>>>>>>>>>>>>>>>>>>>>> Limpiar Trig >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
          if(realizar==1){  
            trig=0;
            __delay_us(4);  
            trig=1;
            __delay_us(10);
            trig=0;
            realizar=0;
           }
        //<<<<<<<<<<<<<<<<<<<<<<<<< IMPRESION EN LCD >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
          //Lcd_Out(1,0,"PERRO");
        sprintf(buffer1,"dis= %3f",distancia);
        Lcd_Out2(1,1,buffer1);
        //__delay_ms(500);
    }
    return (EXIT_SUCCESS);
}

//1cm en 29.2 us
//el tiempo que ser al mitad del que tarda en ir y venir la onda
