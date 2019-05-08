/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 10 de octubre de 2018, 22:12
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"


/*
 * 
 */
#define s1 PORTBbits.RB0
#define s2 PORTBbits.RB1
#define s3 PORTBbits.RB2
#define s4 PORTBbits.RB3
#define s5 PORTBbits.RB4
int adc;
float v0,v1,v2,v3,v4,v5,v6,v7;
int lectura;
float condicion=1.500;
int leersensores(void){
    //if(s1==1){lectura=-2000;}
    //if(s2==1){lectura=-1000;}
    //if(s3==1){lectura=0;}
    //if(s4==1){lectura=1000;}
    //if(s5==1){lectura=2000;}
    //if(s1==0 && s2==0 && s3==0 && s4==0 && s5==0 ){lectura=3333;}
    /*
        011111 = AND7(4)
        011110 = AND6(4)
        011101 = AND5(4)
        011100 = AND4(4)
        011011 = AND3(4)
        011010 = AND2(4)
        011001 = AND1(4)
        011000 = AND0(4)
     
        001111 = ANB7
        001110 = ANB6
        001101 = ANB5
        001100 = ANB4
        001011 = ANB3
        001010 = ANB2
        001001 = ANB1
        001000 = ANB0
     */
    
    //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE B7 <<<<<<<<<<<<<<<<<<<<
        ADPCH=0b001111;//SELECCION DE CANAL ANB7
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v0=adc*5.0/1023.0;//CONVERSION
        __delay_ms(10);
    //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE B6 <<<<<<<<<<<<<<<<<<<<
        ADPCH=0b001110;//SELECCION DE CANAL ANB6
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v1=adc*5.0/1023.0;//CONVERSION
        __delay_ms(10);
    //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE B5 <<<<<<<<<<<<<<<<<<<<
        ADPCH=0b001101;//SELECCION DE CANAL ANB5
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v2=adc*5.0/1023.0;//CONVERSION
        __delay_ms(10);
    //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE B4 <<<<<<<<<<<<<<<<<<<<
        ADPCH=0b001100;//SELECCION DE CANAL ANB4
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v3=adc*5.0/1023.0;//CONVERSION
        __delay_ms(10);
    //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE B3 <<<<<<<<<<<<<<<<<<<<
        ADPCH=0b001011;//SELECCION DE CANAL ANB3
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v4=adc*5.0/1023.0;//CONVERSION
        __delay_ms(10);
    //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE B2 <<<<<<<<<<<<<<<<<<<<
        ADPCH=0b001010;//SELECCION DE CANAL ANB2
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v5=adc*5.0/1023.0;//CONVERSION   
        __delay_ms(10);
   //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE B1 <<<<<<<<<<<<<<<<<<<<
        ADPCH=0b001001;//SELECCION DE CANAL ANB1
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO==1);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v6=adc*5.0/1023.0;//CONVERSION    
    //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE B0 <<<<<<<<<<<<<<<<<<<<
        ADPCH=0b001000;//SELECCION DE CANAL ANB0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO==1);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v7=adc*5.0/1023.0;//CONVERSION
        
       lectura=(0*v0+1000*v1+2000*v2+3000*v3+4000*v4+5000*v5+6000*v6+7000*v7)/
                (v0+v1+v2+v3+v4+v5+v6+v7);
        lectura=lectura-3500;
        
    return lectura;
}
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    //PUERTOS PARA LCD
    PORTC=0;
    PORTD=0;
    ANSELC=0b00000000;
    ANSELD=0b00000000;
    TRISC=0;
    TRISD=0;
    //>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACION PUERTOS PARA ENTRADAS DE SENSOR QTR 8A <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PORTB=0;
    ANSELB=1; //analogico
    TRISB=1; //entrada
    //>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACIONES DEL ADC  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    ADCON0bits.ADON=1;//PRENDER ADC
    ADCON0bits.ADCONT=0;//Operacion normal
    ADCON0bits.ADCS=1; //Clock sourde=FCR
    ADCON0bits.ADFRM=1;//Justificacion derecha
    ADREFbits.ADNREF=0;//Voltaje de referencia negativo = Vss
    ADREFbits.ADPREF=0b00;//Vref=Vdd
    //FVRCONbits.TSEN=1; //ENCENDER ADC
    
    unsigned char buffer1[16],buffer2[16];
    int cont=0;
    
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
     
      Lcd_Cmd(LCD_BLINK_CURSOR_ON);
    __delay_ms(1000);
    Lcd_Cmd(LCD_CURSOR_OFF);
    
    while(1){
        cont=leersensores();
        sprintf(buffer1,"Lectura= %02d",cont);
        Lcd_Out2(1,0,buffer1);
        __delay_ms(100);
    }
    return (EXIT_SUCCESS);
}


