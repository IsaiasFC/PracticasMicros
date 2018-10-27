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
#define led1 LATBbits.LATB7
#define led2 LATBbits.LATB6
#define led3 LATBbits.LATB5
double tiempo=0;
double distancia=0;
int calibracion=1;
unsigned char buffer1[16];

void __interrupt () interrupcion(void){
    //tiempo=(65536/2000000);
    //tiempo=((((double)TMR1H))/2000000);
    //distancia=((34000*tiempo)/2)-calibracion;
    Lcd_Cmd(LCD_CLEAR);
    //sprintf(buffer1,"DisMax=%1f",distancia);
    //Lcd_Out2(1,0,buffer1); 
    Lcd_Out(1,0,"  Interruption");
    led1=0;
    led2=0;
    led3=1;
    __delay_ms(2000);
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
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PUERTOS PARA LEDS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
    PORTB=0;
    ANSELB=0;
    TRISB=0;
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
    T1CLKbits.CS=0b0001;//Frecuencia FOCS/4=0001 
    T1CONbits.nSYNC=1; //NO SINCRONIZADO
    //TMR1=precarga; // PRECARGA 
    //T1GCONbits.GE=0;
     
    //<<<<<<<<<<<<<<<<<<<<<<<<< Iniciar LCD >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
   
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    
    while(1){
        
        //>>>>>>>>>>>>>>>>>>>>>>>>> Limpiar Trig >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            TMR1=0;
            trig=1;
            __delay_us(10);
            trig=0;
            while(echo==0);
            T1CONbits.ON=1; //Inicia el TMR1
            while(echo);
            T1CONbits.ON=0; //Apaga el TMR1
            //tiempo=(((double)TMR1)*94)/250000;
            //distancia=(tiempo*34)-calibracion;
            //tiempo=((TMR1L | (TMR1H<<8))/2000000);
            //distancia=((34000*tiempo)/2)-calibracion;
            tiempo=((((double)TMR1))/2000000);
            distancia=((34000*tiempo)/2)-calibracion;
        //<<<<<<<<<<<<<<<<<<<<<<<<< IMPRESION EN LCD >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        if(distancia>3 && distancia<400){    
            led1=1;
            led2=0;
            led3=0;
        sprintf(buffer1,"Distancia=%1f",distancia);
        Lcd_Out2(1,0,buffer1);
        //Lcd_Out(1,14,"cm");
        }else{
            led1=0;
            led2=1;
            led3=0;
            Lcd_Out(1,0,"Fuera de rango");
            __delay_ms(1000);
            Lcd_Cmd(LCD_CLEAR);
        }
            __delay_ms(1000);
    }
    return (EXIT_SUCCESS);
}

//1cm en 29.2 us
//el tiempo que ser al mitad del que tarda en ir y venir la onda
