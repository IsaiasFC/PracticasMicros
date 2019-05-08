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
#define a LATAbits.LATA0
#define v LATAbits.LATA1
#define r LATAbits.LATA2
#define servo LATAbits.LATA3
#define cambiar PORTBbits.RB0
#define star PORTBbits.RB1

int adressRTC=0b11010000;//0b11010000
int adressRTC_read=0b11010001;//0b11010001
int cseg,cmin,chr,cday,cdate,cmonth,cyear;//VARIABLES DE CONFIGURACION DEL RELOJ
int rseg,rmin,rhr,rday,rdate,rmonth,ryear;//VARIABLES DE LECTURA DEL RELOJ
int dseg,dmin,dhr,dday,ddate,dmonth,dyear;//VARIABLES DE IMPRESION DEL RELOJ
char buffer1[16];

//VARIABLES PARA EL MENU
int iseg=0,imin=0,ihr=0,idate,imonth,iyear;//VARIABLES PARA CONFIGURAR EL BUM!!!!!!!!
int sseg=0,smin=0,shr=0,sdate,smonth,syear;//VARIABLE DE CONFIGURACION DEL RELOJ DENTRO DEL MENU
int seleccion=0;
int inicio=0;
int aux=0,aux2=0,aux3=0,aux4=0,aux5,aux6,aux7;
int auxbum=0;
int i;
void moverservo(int grados){
    switch(grados){
        case 0:
            for(i=0;i<50;i++){
            servo=1;
            __delay_us(600);
            servo=0;
            __delay_us(19000);
            }
            break;
        case 90:
            for(i=0;i<50;i++){
             servo=1;
            __delay_us(1600);
            servo=0;
            __delay_us(19000);
            }
            
            
            break;
        case 180:
            for(i=0;i<50;i++){
             servo=1;
            __delay_us(2600);
            servo=0;
            __delay_us(19000);   
            }
            break;
    }
}

//           00-59  00-59   0-23        1-7     1-31        1-12       0-99
void rtc(int seg,int min, int hr, int day, int date, int month, int year){
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
    SSP1CON2bits.SEN=1; //GENERA SIGNAL DE STAR
    while(SSP1CON2bits.SEN);//ESPERA A QUE el bit sea 
    SSP1BUF=adressRTC;//DIRECCION RTC+bit de escritura
    while(SSP1STATbits.BF);//espera hasta que VACEE EL BUFFER;
    while(SSP1STATbits.R_nW);//espera el 9no ciclo
    //****************************************************verificar si llego un ack o un no ack
    //if(SSP1CON2bits.ACKSTAT==0){v=1;r=0;}else{r=1;}
    //Inicio de escritura en el registro para configuracion de hora
    SSP1BUF=0x00;//comienza a escribir en el registro 0x00 
    while(SSP1STATbits.BF);//ESPERA HASTA QUE 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo 
    SSP1BUF=cseg;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>SEG=00 
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo 
    SSP1BUF=cmin;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MIN
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1BUF=chr;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HR
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1BUF=cday;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DAY 1-7
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1BUF=cdate;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DATE
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1BUF=cmonth;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MONTH
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1BUF=cyear;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>YEAR
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1BUF=0b00010000;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONTROL
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1CON2bits.PEN=1;//generamos un signal de stop
    while(SSP1CON2bits.PEN);
    
    //CONFIGURACION DONE
    v=1;a=0;r=0;
    __delay_ms(500);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>METODO MENU
void menu(){
    if(cambiar==1){
        seleccion=(seleccion + 1);
        if(seleccion==2){seleccion=0;}
        __delay_ms(100);
        Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
        
    }
    switch(seleccion){
        case 0:
            Lcd_Out(2,0,"  CONFIG HOUR");
            break;
        case 1:
            Lcd_Out(2,0,"SEL HOUR BUM!!!");
            break;    
    }
    if(star==1){
        inicio=seleccion;
        __delay_ms(100);
        
        switch(inicio){
            case 0://>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURAR HORA DEL RELOJ
                    v=0;a=0;r=1;
                    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
                    __delay_ms(100);
                    Lcd_Out(1, 0," INICIO CONFIG");
                    Lcd_Out(2, 0,"   DEL RELOJ");
                    __delay_ms(500);
                    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
                    while(aux==0){
                    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>SEG DEL RELOJ
                    while(aux2==0){
                       if(cambiar==1){
                           __delay_ms(100);
                           sseg=sseg+1;
                           if (sseg==59){sseg=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux2=1;}
                       Lcd_Out(1, 0,"   CONFIG SEG");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",shr,smin,sseg,sdate,smonth,syear);
                       Lcd_Out2(2, 1, buffer1);
                    }

                    Lcd_Cmd(LCD_CLEAR);
                    while(aux3==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MIN DEL RELOJ 
                       if(cambiar==1){
                           __delay_ms(100);
                           smin=smin+1;
                           if (smin==59){smin=0;Lcd_Cmd(LCD_CLEAR);}
                           //
                       }
                       if(star==1){__delay_ms(100);aux3=1;}
                       Lcd_Out(1, 0,"   CONFIG MIN");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",shr,smin,sseg,sdate,smonth,syear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux4==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HR DEL RELOJ 
                       if(cambiar==1){
                           __delay_ms(100);
                           shr=shr+1;
                           if (shr==23){shr=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux4=1;}
                       Lcd_Out(1, 0,"   CONFIG HR");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",shr,smin,sseg,sdate,smonth,syear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux5==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DATE DEL RELOJ 
                       if(cambiar==1){
                           __delay_ms(100);
                           sdate=sdate+1;
                           if (sdate==31){sdate=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux5=1;}
                       Lcd_Out(1, 0,"  CONFIG FECHA");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",shr,smin,sseg,sdate,smonth,syear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux6==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MONTH DEL RELOJ 
                       if(cambiar==1){
                           __delay_ms(100);
                           smonth=smonth+1;
                           if (smonth==12){smonth=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux6=1;}
                       Lcd_Out(1, 0,"   CONFIG MES");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",shr,smin,sseg,sdate,smonth,syear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux7==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DATE DEL RELOJ 
                       if(cambiar==1){
                           __delay_ms(100);
                           syear=syear+1;
                           if (syear==31){syear=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux7=1;}
                       Lcd_Out(1, 0,"  CONFIG YEAR");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",shr,smin,sseg,sdate,smonth,syear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    Lcd_Out(1, 0,"     RELOJ");
                    Lcd_Out(2, 0,"  CONFIGURADO");
                    __delay_ms(500);
                    aux=1;
                    Lcd_Cmd(LCD_CLEAR);
                    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

                }
                aux=0;aux2=0;aux3=0;aux4=0,aux5=0,aux6=0,aux7=0;
                rtc(sseg,smin,shr,2,sdate,smonth,syear);// s min hr day date month year
                break;
            case 1://>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURAR HORA DEL BUM
                    v=0;a=0;r=1;
                    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
                    __delay_ms(100);
                    Lcd_Out(1, 0," INICIO CONFIG");
                    Lcd_Out(2, 0,"  DE EXPLOSION");
                    __delay_ms(500);
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux==0){
                    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INGRESAR SEGUNDOS
                    while(aux2==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>SEG DEL BUM
                       if(cambiar==1){
                           __delay_ms(100);
                           iseg=iseg+1;
                           if (iseg==59){iseg=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux2=1;}
                       Lcd_Out(1, 0,"   CONFIG SEG");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",ihr,imin,iseg,idate,imonth,iyear);
                       Lcd_Out2(2, 1, buffer1);
                    }

                    Lcd_Cmd(LCD_CLEAR);
                    while(aux3==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MIN DEL BUM
                       if(cambiar==1){
                           __delay_ms(100);
                           imin=imin+1;
                           if (imin==59){imin=0;Lcd_Cmd(LCD_CLEAR);}
                           //
                       }
                       if(star==1){__delay_ms(100);aux3=1;}
                       Lcd_Out(1, 0,"   CONFIG MIN");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",ihr,imin,iseg,idate,imonth,iyear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux4==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HR DEL BUM
                       if(cambiar==1){
                           __delay_ms(100);
                           ihr=ihr+1;
                           if (ihr==23){ihr=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux4=1;}
                       Lcd_Out(1, 0,"   CONFIG HR");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",ihr,imin,iseg,idate,imonth,iyear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux5==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DATE DEL BUM
                       if(cambiar==1){
                           __delay_ms(100);
                           idate=idate+1;
                           if (idate==31){idate=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux5=1;}
                       Lcd_Out(1, 0,"  CONFIG FECHA");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",ihr,imin,iseg,idate,imonth,iyear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux6==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MONTH DEL BUM
                       if(cambiar==1){
                           __delay_ms(100);
                           imonth=imonth+1;
                           if (imonth==12){imonth=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux6=1;}
                       Lcd_Out(1, 0,"   CONFIG MES");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",ihr,imin,iseg,idate,imonth,iyear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    while(aux7==0){//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DATE DEL BUM
                       if(cambiar==1){
                           __delay_ms(100);
                           iyear=iyear+1;
                           if (iyear==31){iyear=0;Lcd_Cmd(LCD_CLEAR);}

                       }
                       if(star==1){__delay_ms(100);aux7=1;}
                       Lcd_Out(1, 0,"  CONFIG YEAR");
                       sprintf(buffer1,"%d:%d:%d %d/%d/%d",ihr,imin,iseg,idate,imonth,iyear);
                       Lcd_Out2(2, 1, buffer1);
                    }
                    
                    Lcd_Cmd(LCD_CLEAR);
                    Lcd_Out(1, 0,"   EXPLOSION");
                    Lcd_Out(2, 0,"  CONFIGURADA");
                    __delay_ms(500);
                    aux=1;
                    Lcd_Cmd(LCD_CLEAR);
                    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

                }
                aux=0;aux2=0;aux3=0;aux4=0,aux5=0,aux6=0,aux7=0;
                break;
        }
        
        
    }
    
    
    
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>FIN METODO MENU
    

int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Puertos para led y rele
    PORTA=0;
    ANSELA=0;
    TRISA=0;
    //PUERTOS BOTONES CONFIGURACION
    PORTB=0;
    ANSELB=0;
    TRISB=0;
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CONFIGURACION DE PINES PARA LCD
    PORTC=0;
    PORTD=0;
    //ANSELC=0b00000000;
    ANSELCbits.ANSC0=0;
    ANSELCbits.ANSC1=0;
    ANSELCbits.ANSC2=0;
    ANSELCbits.ANSC3=0;
    ANSELCbits.ANSC4=0;
    ANSELCbits.ANSC5=0;
    ANSELCbits.ANSC6=0;
    ANSELCbits.ANSC7=0;
    ANSELD=0b00000000;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Configuracion de pines C como digitales
    //LOS PINES SDA Y SDL ENTRADAS DIGITALES <<<<<<<<<<<<<<<<<<<<<<<<<<<< POR PPS SI CONFIGURACION ESTAN EN B1 SCL2 Y B2 SDA2 ///////////SCL1 RC3 Y SDA1 RC4
    SSP1CLKPPS=0x13;// PAGINA 237 y 236 //RC3
    SSP1DATPPS=0x14;    //RC4
    RC3PPS=0x14;
    RC4PPS=0x15;
    /*
     RB0 0x08
     RB1 0x09
     */
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>I2C CONFIGURATIONS
    SSP1CON1bits.SSPEN=1;
    SSP1CON1bits.SSPM=0b1000;
    SSP1ADD=0x13;//13 //IGUAL A 19
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Iniciamos LCD
    Lcd_Init();     //inicializamos el lcd
    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
    Lcd_Cmd(LCD_CURSOR_OFF);	//apagamos el cursor
    __delay_ms(1000);
    //Lcd_Out(2, 0, "RELOG");	//escribimos en la linea 2 espacio 1 la palabra mkmekatronika
    rtc(0,00,0,5,0,0,0); //CONFIGURAMOS EL RTC CON LOS DATOS DESEADOS
    moverservo(90);
    while(1){
        SSP1CON2bits.SEN=1; //GENERA SIGNAL DE STAR
        while(SSP1CON2bits.SEN);//ESPERA A QUE el bit sea 
        SSP1BUF=adressRTC;//DIRECCION RTC+bit de escritura
        while(SSP1STATbits.BF);//espera hasta que VACEE EL BUFFER;
        while(SSP1STATbits.R_nW);//espera el 9no ciclo
        SSP1BUF=0x00;//Se escribe el siguiente dato //0x00
        while(SSP1STATbits.BF);//ESPERA HASTA QUE 
        while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo 
        SSP1CON2bits.RSEN=1; //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>GENERA SIGNAL DE RESTAR
        while(SSP1CON2bits.RSEN);
        SSP1BUF=adressRTC_read;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DIRECCION RTC+bit de LECTURA >>>>adressRTC_read
        while(SSP1STATbits.BF);//ESPERA HASTA QUE 
        while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
        SSP1CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP1STATbits.BF==0);
        rseg=SSP1BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato segundos
        SSP1CON2bits.ACKDT=0;
        SSP1CON2bits.ACKEN=1; //GENERA ACK
        while(SSP1CON2bits.ACKEN); 
        SSP1CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP1STATbits.BF==0);
        rmin=SSP1BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato minutos
        SSP1CON2bits.ACKDT=0;
        SSP1CON2bits.ACKEN=1; //GENERA ACK
        while(SSP1CON2bits.ACKEN);
        SSP1CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP1STATbits.BF==0);
        rhr=SSP1BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato hr
        SSP1CON2bits.ACKDT=0;
        SSP1CON2bits.ACKEN=1; //GENERA ACK
        while(SSP1CON2bits.ACKEN);
        SSP1CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP1STATbits.BF==0);
        rday=SSP1BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato day
        SSP1CON2bits.ACKDT=0;
        SSP1CON2bits.ACKEN=1; //GENERA ACK
        while(SSP1CON2bits.ACKEN);
        SSP1CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP1STATbits.BF==0);
        rdate=SSP1BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato date
        SSP1CON2bits.ACKDT=0;
        SSP1CON2bits.ACKEN=1; //GENERA ACK
        while(SSP1CON2bits.ACKEN);
        SSP1CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP1STATbits.BF==0);
        rmonth=SSP1BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato month
        SSP1CON2bits.ACKDT=0;
        SSP1CON2bits.ACKEN=1; //GENERA ACK
        while(SSP1CON2bits.ACKEN);
        SSP1CON2bits.RCEN=1;//HAbilita la recepcion
        while(SSP1STATbits.BF==0);
        ryear=SSP1BUF;//>>>>>>>>>>>>>>>>>>>>>>>lee dato year
        
        SSP1CON2bits.ACKDT=1;
        SSP1CON2bits.ACKEN=1; //GENERA NOACK
        while(SSP1CON2bits.ACKEN);
        
        SSP1CON2bits.PEN=1;//generamos un signal de stop
        while(SSP1CON2bits.PEN);
          
        dseg=((0b01110000 & rseg)>>4)*10+(0b00001111 & rseg);
        dmin=((0b01110000 & rmin)>>4)*10+(0b00001111 & rmin);
        dhr=((0b01110000 & rhr)>>4)*10+(0b00001111 & rhr);
        ddate=((0b01110000 & rdate)>>4)*10+(0b00001111 & rdate);
        dmonth=((0b01110000 & rmonth)>>4)*10+(0b00001111 & rmonth);
        dyear=((0b11110000 & ryear)>>4)*10+(0b00001111 & ryear);
        
        sprintf(buffer1,"%d:%d:%d  %d/%d",dhr,dmin,dseg,ddate,dmonth);
        Lcd_Out2(1, 0, buffer1);
        
        v=0;a=1;r=0;
        menu();
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>verificar explosion
        if(dhr==ihr && dmin==imin && dseg==iseg && ddate==idate && dmonth==imonth){
            
            while(aux==0){
            Lcd_Cmd(LCD_CLEAR);
            Lcd_Out(1, 0,"   BUM!!!!!!!");
            Lcd_Out(2, 0,"TIME OVER :3");
            
            if(star==1){aux=1;}
            //v=0;a=1;r=1;
            //for(int i=0;i<30;i++){
              v=1;a=0;r=0;
              __delay_ms(50);
              v=0;a=1;r=0;
              if(star==1){aux=1;}
              __delay_ms(50);
              v=0;a=0;r=1;
              if(star==1){aux=1;}
              __delay_ms(50);
            //}
              if(auxbum==0){moverservo(0);auxbum=1;}
            }
            auxbum=0;
            moverservo(90);
            aux=0;
            Lcd_Cmd(LCD_CLEAR);
            RB0PPS=0x00;
        }
        if(dseg==59){Lcd_Cmd(LCD_CLEAR);}
        //__delay_ms(900);
    }
    return (EXIT_SUCCESS);
}

