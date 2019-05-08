/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 15 de noviembre de 2018, 2:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"
#include "DS1307.c"

int cseg,cmin,chr,cday,cdate,cmonth,cyear;
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTA=0;
    ANSELA=0;
    TRISA=0;
    //ANSELAbits.ANSA0;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURACION DE PINES PARA LCD
    PORTC=0;
    PORTD=0;
    ANSELCbits.ANSC0=0;
    ANSELCbits.ANSC1=0;
    ANSELCbits.ANSC2=0;
    //ANSELCbits.ANSC3=0;
    //ANSELCbits.ANSC4=0;
    ANSELCbits.ANSC5=0;
    ANSELCbits.ANSC6=0;
    ANSELCbits.ANSC7=0;
    ANSELD=0b00000000;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>I2C CONFIGURATIONS
   // SSP1CON1bits.SSPEN=1;
   // SSP1CON1bits.SSPM=0b1000;
   // SSP1ADD=19;//13 //IGUAL A 19
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Iniciamos LCD
    Lcd_Init();     //inicializamos el lcd
    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
    Lcd_Cmd(LCD_CURSOR_OFF);	//apagamos el cursor
    __delay_ms(1000);
    while(1){
    
    }
    return (EXIT_SUCCESS);
}

