/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 14 de noviembre de 2018, 13:42
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include <xc.h>
#include "flex_lcd.h"

/*
 * 
 */
int contint=0,conts=0,contmin=50,conthr=11;
int precarga=15536;//15536 chida
char buffer1[16];
void bum(int hr,int min,int seg){
    if(conthr==hr && contmin==min && conts==seg){
        LATAbits.LATA0=1;
    }
}
void __interrupt () interrupcion(void){
    if(contint<13){//13chido
        contint=contint+1;
    }else{//se cumple un segundo
            if(conts<59){
                conts=conts+1;
            }else{//se cumple un minuto
                if(contmin<59){
                    contmin=contmin+1;
                }else{//se cumple una hora
                    if(conthr<23){
                        conthr=conthr+1;
                    }else{//se cumple un dia
                        conthr=0;
                        
                    }
                    contmin=0;
                    
                }
                conts=0;
                Lcd_Cmd(LCD_CLEAR);
            }    
            contint=0;
           // Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1,"    %d:%d:%d",conthr,contmin,conts);
            Lcd_Out(2, 0, "Mecatronica");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
            Lcd_Out2(1, 1, buffer1);
            bum(11,51,0);// hr min seg
    }
    
    PIR4bits.TMR1IF=0; //Limpia bandera de timer 1
}

int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>PINES LED
    PORTA=0;
    ANSELA=0;
    TRISA=0;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURACION DE PINES PARA LCD
    PORTC=0;
    PORTD=0;
    ANSELC=0b00000000;
    ANSELD=0b00000000;
      //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Configuracion de interrupciones 
    PIR4bits.TMR1IF=0; //Limpia bandera de timer 1
    PIE4bits.TMR1IE=1;//Habilita interrupcion por timer 1
    INTCONbits.GIE=1; //Habilita interrupcion global
    INTCONbits.PEIE=1; // habilita interrupcion por periferico
    PIE4bits.TMR1IE=1;
     //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURACION DE TMR1
    T1CONbits.CKPS=0b11; //PREESCALER    
    T1CLKbits.CS=0b0001;//Frecuencia FOCS/4=0001    FOSC=0010
    T1CONbits.nSYNC=1; //NO SINCRONIZADO
    TMR1=precarga; // PRECARGA 
    T1CONbits.ON=1; //Inicia el TMR1
    /*
     * CKPS<1:0>: Timer1 Input Clock Prescale Select bits
        11 = 1:8 Prescale value
        10 = 1:4 Prescale value
        01 = 1:2 Prescale value
        00 = 1:1 Prescale value
     */
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Iniciamos LCD
    Lcd_Init();     //inicializamos el lcd
    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
    Lcd_Cmd(LCD_CURSOR_OFF);	//apagamos el cursor
    __delay_ms(1000);
    
    while(1){ //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>WHILE INFINITO
        //Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        //Lcd_Out(2, 0, "Mecatronica");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        
        //__delay_ms(900);
    }
    return (EXIT_SUCCESS);
}

