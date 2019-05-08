
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000
/*
 * 
 */
int adc=0;
int aux=0;
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110; //**velocidad del oscilador
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PUERTO
    PORTB=0; //LIMPA
    ANSELB=0; //PUERTO B COMO DIGITAL
    TRISB=255; //PUERTO B COMO ENTRADA
    
    PORTA=0; //LIMPA
    ANSELA=1; //PUERTO A COMO DIGITAL
    TRISA=255; //PUERTO A COMO ENTRADA
    
    PORTD=0;
    ANSELD=0;
    TRISDbits.TRISD6=0;
    TRISDbits.TRISD7=0;
     //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACIONES DEL ADC  
    ADCON0bits.ADON=1;//PRENDER ADC
    ADCON0bits.ADCONT=0;//Operacion normal
    ADCON0bits.ADCS=1; //Clock sourde=FCR
    ADCON0bits.ADFRM=1;//Justificacion derecha
    ADREFbits.ADNREF=0;//Voltaje de referencia negativo = Vss
    ADREFbits.ADPREF=0b00;//Vref=Vdd
    ADPCH=0b00000000;//SELECCION DE CANAL ANA0
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>PPS
    RB0PPS=0x09; //MODULO CCP1 SALDRA POR RB0
    RB1PPS=0x09; //MODULO CCP1 SALDRA POR RB0
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>TMR2
    T2CLKCON=0b0001;// CS=FOSC/4
    T2CONbits.ON=1; //ENCENDER TIMER2
    T2CONbits.OUTPS=0; //POSTESCALER 1:1
    T2CONbits.CKPS=0b100; //PRESCALER 1:16
    PR2=255; //FRECUENCIA DE 1.95 KHZ
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CCP1
    CCP1CONbits.EN=1; //HABILITA  EL MODULO CCP1
    CCP1CONbits.FMT=0; //ALENEACION A LA DERECHA CCPR1H, L
    CCP1CONbits.MODE=0b1111; //MODO PWM
    CCPTMRS0bits.C1TSEL=0b01; //timer2 CCP1
    //TRISB=0;//PUERTO B COMO SALIDA
    while(1){
        //>>>>>>>>>>>>>>>>>> LETURA ANALOGICA DE A0 <<<<<<<<<<<<<<<<<<<<
        
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        aux=adc*1.0;
        
        if(aux>0 && aux<512){
            //LATDbits.LATD6=1;
            //LATDbits.LATD7=0;
            TRISBbits.TRISB0=0;//BO COMO SALIDA
            TRISBbits.TRISB1=1;//B1 COMO ENTRADA
            //RB0PPS=0x09; //MODULO CCP1 SALDRA POR RB0
            CCPR1=aux;
        }
        if(aux>512 && aux<1024){
             //LATDbits.LATD6=0;
            //LATDbits.LATD7=1;
            TRISBbits.TRISB0=1; //B0 COMO ENTRADA
            TRISBbits.TRISB1=0; // B1 COMO SALIDA
            
            CCPR1=aux;
        }
        if(aux==512){
            // LATDbits.LATD6=0;
            // LATDbits.LATD7=0;
           TRISBbits.TRISB0=1; //B0 COMO ENTRADA
           TRISBbits.TRISB1=1; // B1 COMO SALIDA
           __delay_ms(250);
        }
        __delay_ms(10);
        
        //v0=adc*5.0/1023.0;//CONVERSION
        
        
        /*for(x=0;x<1024;x++){
        __delay_ms(10);
        CCPR1=x;//define el ciclo de trabajo
        }*/
    }
    //>>> FRECUENCIA DE  KHz<<<    
    return (EXIT_SUCCESS);
}

