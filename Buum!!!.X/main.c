/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 12 de noviembre de 2018, 19:21
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"
#define r LATAbits.LATA2
#define a LATAbits.LATA0
#define v LATAbits.LATA1

int adressRTC=0xD0;//0b11010000
int adressRTC_read=0xD1;//0b11010001
int cseg,cmin,chr,cday,cdate,cmonth,cyear;
int rseg,rmin,rhr,dseg,dmin,dhr;
char buffer1[16];
//           00-59  00-59   0-23        1-7     1-31        1-12       0-99
void crtc(int seg,int min, int hr, int day, int date, int month, int year){
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //>>>>>>>>>>>> SEGUNDOS
    if(seg<10){
        cseg=0b0000000+seg;
    }else{
        cseg=((seg/10)<<4)+(seg-((seg/10)*10));
        //seg=(8<<4)+3; seg=0b10000101
        
        //n-((n/10)*10)
    }
    //>>>>>>>>>>>>MINUTOS
    if(min<10){
        cmin=min;
    }else{
        cmin=((min/10)<<4)+(min-((min/10)*10));
    }
    //>>>>>>>>>>>>HR FORMATO 24HR
    if(hr<10){
        chr=0b00000000+hr;
        //0b00010101;//HR=15
    }else{
        chr=((hr/10)<<4)+(hr-((hr/10)*10));
    }
    //>>>>>>>>>>>>DAY
    cday=day;
    //>>>>>>>>>>>>DATE
    if(date<10){
        cdate=date;
    }else{
        cdate=((date/10)<<4)+(date-((date/10)*10));
    }
    //>>>>>>>>>>>>MONTH
    
    if(month<10){
        cmonth=month;
    }else{
        cmonth=((month/10)<<4)+(month-((month/10)*10));
    }
    //>>>>>>>>>>>>YEAR
    if(year<10){
        cyear=year;
    }else{
        cyear=((year/10)<<4)+(year-((year/10)*10));
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>TRAMA DE ESCRITURA PARA CONFIGURACION INICIAL 
    SSP2CON2bits.SEN=1; //GENERA SIGNAL DE STAR
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "STAR");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        r=1;
        __delay_ms(1000);
        
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
    while(SSP2CON2bits.SEN);//ESPERA A QUE el bit sea 
    SSP2BUF=adressRTC;//DIRECCION RTC+bit de escritura
   
    while(SSP2STATbits.BF);//espera hasta que VACEE EL BUFFER;
    while(SSP2STATbits.R_nW);//espera el 9no ciclo
    //****************************************************verificar si llego un ack o un no ack
    if(SSP2CON2bits.ACKSTAT==0){v=1;r=0;}else{r=1;}
    //Inicio de escritura en el registro para configuracion de hora
    SSP2BUF=0x00;//comienza a escribir en el registro 0x00 
    while(SSP2STATbits.BF);//ESPERA HASTA QUE 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo 
    SSP2BUF=cseg;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>SEG=00 
    while(SSP2STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo 
    SSP2BUF=cmin;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MIN
    while(SSP2STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP2BUF=chr;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HR
    while(SSP2STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP2BUF=cday;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DAY 1-7
    while(SSP2STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP2BUF=cdate;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DATE
    while(SSP2STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP2BUF=cmonth;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MONTH
    while(SSP2STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP2BUF=cyear;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>YEAR
    while(SSP2STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP2BUF=0b00010000;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONTROL
    while(SSP2STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP2CON2bits.PEN=1;//generamos un signal de stop
    while(SSP2CON2bits.PEN);
    
    Lcd_Out(2, 0, "CONF DONE");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
    __delay_ms(1500);
}
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
    //ANSELC=0b00000000;
    ANSELCbits.ANSC0=0;
    ANSELCbits.ANSC1=0;
    ANSELCbits.ANSC2=0;
    //ANSELCbits.ANSC3=0;
    //ANSELCbits.ANSC4=0;
    ANSELCbits.ANSC5=0;
    ANSELCbits.ANSC6=0;
    ANSELCbits.ANSC7=0;
    ANSELD=0b00000000;
    //TRISC=0;
    //TRISD=0;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Configuracion de pines C como digitales
    //ANSELC=0;
    //TRISCbits.TRISC3=1;
    //TRISCbits.TRISC4=1;
    //WPUCbits.WPUC3=1;
    //WPUCbits.WPUC4=1;
    //LOS PINES SDA Y SDL ENTRADAS DIGITALES <<<<<<<<<<<<<<<<<<<<<<<<<<<< POR PPS SI CONFIGURACION ESTAN EN B1 SCL2 Y B2 SDA2 ///////////SCL1 RC3 Y SDA1 RC4
    SSP2CLKPPS=0x09;// PAGINA 237 y 236 //RC3=0x13 b1=0x09
    SSP2DATPPS=0x0A;    //RC4=0x14 b2=0x0A
    ANSELB=0;
    TRISBbits.TRISB1=1;
    TRISBbits.TRISB2=1;
    WPUBbits.WPUB1=1;
    WPUBbits.WPUB2=1;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>I2C CONFIGURATIONS
    SSP2CON1bits.SSPEN=1;
    //SSP1CON1bits.SSPM=0b1000;
    SSP2CON1bits.SSPM3=1 ;
    SSP2CON1bits.SSPM2=0;
    SSP2CON1bits.SSPM1=0;
    SSP2CON1bits.SSPM0=0;
    SSP2ADD=0x13;//13 //IGUAL A 19
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Iniciamos LCD
    Lcd_Init();     //inicializamos el lcd
    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
    Lcd_Cmd(LCD_CURSOR_OFF);	//apagamos el cursor
    __delay_ms(1000);
    //Lcd_Out(2, 0, "RELOG");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
    crtc(0,02,20,2,13,11,18); //CONFIGURAMOS EL RTC CON LOS DATOS DESEADOS
    
    while(1){
        SSP2CON2bits.SEN=1; //GENERA SIGNAL DE STAR
        while(SSP2CON2bits.SEN);//ESPERA A QUE el bit sea 
        SSP2BUF=adressRTC;//DIRECCION RTC+bit de escritura
        while(SSP2STATbits.BF);//espera hasta que VACEE EL BUFFER;
        while(SSP2STATbits.R_nW);//espera el 9no ciclo
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "STAR");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        __delay_ms(1000);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
        SSP2BUF=0x00;//Se escribe el siguiente dato //0x00
        while(SSP2STATbits.BF);//ESPERA HASTA QUE 
        while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo 
        SSP2CON2bits.RSEN=1; //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>GENERA SIGNAL DE RESTAR
        while(SSP2CON2bits.RSEN);
        SSP2BUF=adressRTC_read;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DIRECCION RTC+bit de LECTURA >>>>adressRTC_read
        while(SSP2STATbits.BF);//ESPERA HASTA QUE 
        while(SSP2STATbits.R_nW);//ESPERA EL 9no ciclo
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "RESTAR");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        __delay_ms(1000);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        SSP2CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP2STATbits.BF==0);//+++++++++++++++++++++++++++++++==0
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "while BF");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        __delay_ms(1000);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
        rseg=SSP2BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato segundos
        SSP2CON2bits.ACKDT=0;
        SSP2CON2bits.ACKEN=1; //GENERA ACK
         while(SSP2CON2bits.ACKEN);//++++++++++++++++++++++++++++sin ==0  
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "s leidos");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        __delay_ms(1000);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      
        SSP2CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP2STATbits.BF==0);//+++++++++++++++++++++++++++++++++++++++==0
        rmin=SSP2BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato minutos
        SSP2CON2bits.ACKDT=0;
        SSP2CON2bits.ACKEN=1; //GENERA ACK
        while(SSP2CON2bits.ACKEN);//++++++++++++++++++++++++++++++++++++++++++++sin ==0
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "min leidos");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        __delay_ms(1000);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
        SSP2CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP2STATbits.BF==0);//+++++++++++++++++++++++++++++++++++++++++++++++++++==0
        rhr=SSP2BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato hr
        SSP2CON2bits.ACKDT=1;
        SSP2CON2bits.ACKEN=1; //GENERA NOACK
        while(SSP2CON2bits.ACKEN);//++++++++++++++++++++++++++++++++++++++++++++++sin ==0
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "hr leidos");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        __delay_ms(1000);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
        SSP2CON2bits.PEN=1;//generamos un signal de stop
        while(SSP2CON2bits.PEN);
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "STOP");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        __delay_ms(1000);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
        dseg=((0b01110000 & rseg)>>4)*10+(0b00001111 & rseg);
        dmin=((0b01110000 & rmin)>>4)*10+(0b00001111 & rmin);
        dhr=((0b01110000 & rhr)>>4)*10+(0b00001111 & rhr);
        if(dseg==9){LATAbits.LATA0=LATAbits.LATA0+1;}
        sprintf(buffer1,"   %d:%d:%d",dhr,dmin,dseg);
        Lcd_Out2(1, 1, buffer1);
        __delay_ms(2000);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Lcd_Cmd(LCD_CLEAR);		//limpiamos el cursor
        Lcd_Out(2, 0, "READ DONE");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
        __delay_ms(1500);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
    }
    return (EXIT_SUCCESS);
}

