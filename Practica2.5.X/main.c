/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 10 de septiembre de 2018, 14:49
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd_1.h"


/*
 * 
 */
int main(int argc, char** argv) {
    //cariables
    int adc, adc1, adc2;
    float voltaje,temp,tempin;
    
    unsigned char buffer1[16];
    
    OSCFRQbits.HFFRQ=0b110;
    ANSELC=0b00000000;
    ANSELD=0b00000000;
    PORTA=0;
    PORTB=0;
    // Configuracion del canal
    ANSELAbits.ANSA0=1;
    TRISAbits.TRISA0=1; 
    ANSELEbits.ANSE2=1;
    TRISEbits.TRISE2=1; 
    
    //CONFIGURACION DEL ADC
    //TODOS LOS PINES QUE USEN ADC DEBEN DE ESTAR DECLARADOS COMO ENTRADAS ANALOGICAS
    ADCON0bits.ADON=1;//PRENDER ADC
    ADCON0bits.ADCONT=0;//Operacion normal
    ADCON0bits.ADCS=1; //Clock sourde=FCR
    ADCON0bits.ADFRM=1;//Justificacion derecha
    ADREFbits.ADNREF=0;//Voltaje de referencia = Vss
    ADREFbits.ADPREF=0b00;//Vref=Vdd
    FVRCONbits.TSEN=1;
   
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(200);
   while(1){
        //CANAL A0 pagina 355 datasheet
        /*
         CANCAL PARA INDICADOR DE TEMPERATURA
         * 111101 = Temperature Indicator
         *///CANAL A1 lm35
       /* 
        
        ADPCH=0b111101;//SELECCION DE CANAL TEN INTERNA, ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        __delay_ms(20);
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO==1);//Esperar a que terimine la conversion
        //ADCON0bits.DONE=1;
        adc=ADRESH;
        //RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc<<8;
        //SUMA LOS 8 BITS FALTANTES 0000001111111111;
        adc=adc+ADRESL;
        
        //CONVERSION
        //tempin=(adc*5/1023)*100;
        //tempin=(0.659-(5/4)*(1-(adc)/(1024-1)))/(0.00132)-40;
        tempin=0.659-(((0.659-(5/4)*(1-(adc)/(1024-1)))/(0.00132)-40)+40)*0.00132;
        //__delay_ms(100);*/
        ADPCH=0b100010;//SELECCION DE CANAL ANSB3, ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        __delay_us(20);
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO==1);//Esperar a que terimine la conversion
        //ADCON0bits.DONE=1;
        adc1=ADRESH;
        //RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc1=adc1<<8;
        //SUMA LOS 8 BITS FALTANTES 0000001111111111;
        adc1=adc1+ADRESL;
        //CONVERSION
        
        temp=(adc1*5.0/1023.0)*100.0;
        
        
        //__delay_ms(100);
        ADPCH=0b000000;//SELECCION DE CANAL ANSA0, ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        __delay_us(20);
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO==1);//Esperar a que terimine la conversion
        //ADCON0bits.DONE=1;
        //SUMAR LOS DOS REGISTROS DE CONVERSION 
        //PRIMEROS 2 BITS 0000000000000011
        adc2=ADRESH;
        //RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc2=adc2<<8;
        //SUMA LOS 8 BITS FALTANTES 0000001111111111;
        adc2=adc2+ADRESL;
        //CONVERSION
       voltaje=adc2*5.0/1023.0;
       
        sprintf(buffer1,"Vp=%.2f",voltaje);
        Lcd_Out2(1,0,buffer1);
        sprintf(buffer1,"Te=%.2f",temp);
        Lcd_Out2(2,0,buffer1);
       // sprintf(buffer1,"Ti=%.2f",tempin);
        //Lcd_Out2(2,0,buffer1);
        
        __delay_ms(200);
        //Lcd_Out(2,0,"ESTA!!!");
        
        
    }
        
    
    return (EXIT_SUCCESS);
}

