/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 10 de septiembre de 2018, 14:49
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include"config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"






void main(void) {
    
    //**VARIABLES A UTILIZAR
    int adc1, adc2;
    float temp_reference, temp_lm35, volt;
    unsigned char buffer1[16];
   
    
    //**CONFIGURACION DE OSCILADOR
     OSCFRQbits.HFFRQ=0b110;
     
    //**CONFIGURACION DE PUERTOS COMO DIGITAL
     //**LCD
     
    ANSELC=0b00000000;
    ANSELD=0b00000000;
    
    //**PUERTO PARA CONMUTACION DE RELEVADOR
    ANSELCbits.ANSC2=0;
    TRISCbits.TRISC2=0;
    
    //**PUERTOS ANALOGICOS PARA ENTRADAS DE SENSOR Y POTENCIOMETRO
	ANSELAbits.ANSA0=1;
    TRISAbits.TRISA0=1;
    TRISAbits.TRISA1=1;
    ANSELAbits.ANSA1=1;
      
      //**CONFIGURACION DE ADC
      
      ADCON0bits.ADON=1; //**ADC ENCENDIDO
      ADCON0bits.ADCONT=0;
      ADCON0bits.ADCS=1; //**FRECUENCIA DE CONVERSION
      ADCON0bits.ADFRM=1; //**JUSTIFICACION 1 = DERECHA 0 = LEFT
      ADREFbits.ADNREF=0; //**REFERENCIA NEGATIVA VSS
      ADREFbits.ADPREF=0b00; //**REFERENCIA POSOTIVA Vdd

      
      //**CONFIGURACION DE LCD
      
      Lcd_Init();//**INICIALIZA LCD
    Lcd_Cmd(1);//**LIMPIA LCD
    Lcd_Cmd(12);//**APAGA EL CURSOR
    __delay_ms(100);
        
    //**INICIACION DEL CICLO INFINITO DE OPERACION
        while (1){
          
            ADPCH=0b000001;//**SELECCION DEL PUERTO A1
                __delay_us(20);
         ADCON0bits.ADGO=1; //**INICIACION DE CONVERSION
         while(ADCON0bits.ADGO==1); 
         adc1=ADRESH; 
         adc1=adc1<<8; //**RECORRIDO DE BITS IZQUIERDA
         adc1=adc1+ADRESL;
         volt=adc1*5.0/1024.0;
         temp_lm35=volt*100;
         
//**INICIO DE CONVERSION 2<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
         
          ADPCH=0b000000;//SELECCION DE CANAL A0
          __delay_us(20);
           ADCON0bits.ADGO=1;//**INICIO DE CONVERSION
           while(ADCON0bits.ADGO==1);
         adc2=ADRESH;
         adc2=adc2<<8; //**RECORRIDO A LA IZQUIERDA
         adc2=adc2+ADRESL;
         temp_reference=(adc2*5.0/1024.0)*16;//**CONVERSION A VOLTAGE
         
         //**IMPRESION DE DATOS 
          sprintf(buffer1,"Real=%04.0f",temp_lm35);
         Lcd_Out2(2,1,buffer1);
         __delay_ms(100);
         //*********************LCD2
         
          sprintf(buffer1,"TempWish=%04.0f",temp_reference);
         Lcd_Out2(1,2,buffer1);
         __delay_ms(100);
         
          
         //**CONDICIONES DE BRECHAS DIFERENCIALES
    if (temp_reference - 5 > temp_lm35 )
    {
        LATCbits.LATC2=0;
    }
    else
        LATCbits.LATC2=1;
        
        
     if(temp_reference + 5 < temp_lm35)
    {
        LATCbits.LATC2=1;
        
    }
     else
         LATCbits.LATC2=0;
    
           
        }

    return;
}