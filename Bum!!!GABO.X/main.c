/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 15 de noviembre de 2018, 13:16
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"
#include <xc.h>

int adress_rtc_write=0xD0;//0b11010000
int adress_rtc_read=0xD1;//0b11010001
int cseg,cmin,chr,cday,cdate,cmonth,cyear;
int rseg,rmin,rhr,dseg,dmin,dhr;
char buffer1[16];
void conf_RTC(int seg,int min, int hr, int day, int date, int month, int year){
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SEGUNDOS
    if(seg<10){
        cseg=0b0000000+seg;
    }else{
        cseg=((seg/10)<<4)+(seg-((seg/10)*10));
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MINUTOS
    if(min<10){
        cmin=min;
    }else{
        cmin=((min/10)<<4)+(min-((min/10)*10));
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HR FORMATO 24HR
    if(hr<10){
        chr=0b00000000+hr;
        //0b00010101;//HR=15
    }else{
        chr=((hr/10)<<4)+(hr-((hr/10)*10));
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DAY
    cday=day;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DATE
    if(date<10){
        cdate=date;
    }else{
        cdate=((date/10)<<4)+(date-((date/10)*10));
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MONTH
    
    if(month<10){
        cmonth=month;
    }else{
        cmonth=((month/10)<<4)+(month-((month/10)*10));
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>YEAR
    if(year<10){
        cyear=year;
    }else{
        cyear=((year/10)<<4)+(year-((year/10)*10));
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURACION RTC
    
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
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURACION PARA I2C 
    TRISCbits.TRISC3=1;//entradas digitales
    TRISCbits.TRISC4=1;
    SSP1CLKPPS=0x13;// PAGINA 237 y 236 //RC3=0x13 b1=0x09
    SSP1DATPPS=0x14;    //RC4=0x14 b2=0x0A
    SSP1CON1bits.SSPEN=1;    
    SSP1CON1bits.SSPM3=1 ;
    SSP1CON1bits.SSPM2=0;
    SSP1CON1bits.SSPM1=0;
    SSP1CON1bits.SSPM0=0;
    SSP1ADD=19
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Iniciamos LCD
    Lcd_Init();     //inicializamos el lcd
    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
    Lcd_Cmd(LCD_CURSOR_OFF);	//apagamos el cursor
    __delay_ms(1000);
    //Lcd_Out(2, 0, "RELOG");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
    while(1){
        
        
    }
    return (EXIT_SUCCESS);
}

