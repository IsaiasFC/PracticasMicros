/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 24 de octubre de 2018, 19:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f18877.h>
#include "config.h"
#define _XTAL_FREQ 32000000

#define mderdel TRISBbits.TRISB0 //Motor DERECHO DELANTE
#define mderatraz TRISBbits.TRISB1 //Motor DERECHO ATRAZ

#define mizqdel TRISBbits.TRISB2 //MOTOR IZQUIERDO DELANTE
#define mizqatraz TRISBbits.TRISB3 //MOTOR IZQUIERDO ATRAZ

int error=0, errorant=0;
//float kp=150,kd=100,ki=60;
double kp=0.2,kd=0.046,ki=60;
int velocidad=800;
int adc;
float v0,v1,v2,v3,v4,v5,v6,v7;
void geterror(void){
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lectura de A0
        ADPCH=0b000000;//SELECCION DE CANAL ANA0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v0=adc*5.0/1023.0;//CONVERSION   
        
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lectura de A1
        ADPCH=0b000001;//SELECCION DE CANAL ANA0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v1=adc*5.0/1023.0;//CONVERSION   
        
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lectura de A2
        ADPCH=0b000010;//SELECCION DE CANAL ANA0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v2=adc*5.0/1023.0;//CONVERSION   
        
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lectura de A3
        ADPCH=0b000011;//SELECCION DE CANAL ANA0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v3=adc*5.0/1023.0;//CONVERSION   
        
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lectura de A4
        ADPCH=0b000100;//SELECCION DE CANAL ANA0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v4=adc*5.0/1023.0;//CONVERSION   
       
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lectura de A5
        ADPCH=0b000101;//SELECCION DE CANAL ANA0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v5=adc*5.0/1023.0;//CONVERSION   
        
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lectura de A6
        ADPCH=0b000110;//SELECCION DE CANAL ANA0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v6=adc*5.0/1023.0;//CONVERSION   
       
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lectura de A7 
        ADPCH=0b000111;//SELECCION DE CANAL ANA0
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v7=adc*5.0/1023.0;//CONVERSION  
        
        
       error=(int)((0*v0+1000.0*v1+2000.0*v2+3000.0*v3+4000.0*v4+5000.0*v5+6000.0*v6+7000.0*v7)/(v0+v1+v2+v3+v4+v5+v6+v7));
       error=error-3500;
        
        
}
void formula(void){
    PORTB=0;
    TRISB=0b11111111;
    if(error<-500){
        
        //IZQUIERDA
        mderdel=0;
        mderatraz=1;
        mizqdel=1;
        mizqatraz=0;
        CCPR1=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
        CCPR2=0;
        CCPR3=0;
        CCPR4=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
        
    }else if(error>500){
        
        //DERECHA
        mderdel=1;
        mderatraz=0;
        mizqdel=0;
        mizqatraz=1;
        CCPR1=0;
        CCPR2=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
        CCPR3=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
        CCPR4=0;
    }else {
        
        
        
        //delante
        mderdel=0;
        mderatraz=0;
        mizqdel=0;
        mizqatraz=0;
        
        
        if(error<0){
            CCPR1=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
            CCPR2=0;
            CCPR3=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
            CCPR4=0;
        }else{
            CCPR1=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
            CCPR2=0;
            CCPR3=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
            CCPR4=0;
        }
        //__delay_ms(10);
    }
}
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACION PUERTOS PARA ENTRADAS DE SENSOR  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PORTA=0;
    ANSELA=0b11111111; //digital
    TRISA=0b11111111; //entrada
    PORTC=0;
    ANSELC=0b11111111;
    TRISCbits.TRISC0=1;
    //>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACIONES DEL ADC PARA ENTRADAS ANALOGICAS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    /*  //Seleccion del canal de ADPCH=0b001000
        100010 = ANE2(4)
        100001 = ANE1(4)
        100000 = ANE0(4)
        011111 = AND7(4)
        011110 = AND6(4)
        011101 = AND5(4)
        011100 = AND4(4)
        011011 = AND3(4)
        011010 = AND2(4)
        011001 = AND1(4)
        011000 = AND0(4)
        010111 = ANC7
        010110 = ANC6
        010101 = ANC5
        010100 = ANC4
        010011 = ANC3
        010010 = ANC2
        010001 = ANC1
        010000 = ANC0
        001111 = ANB7
        001110 = ANB6
        001101 = ANB5
        001100 = ANB4
        001011 = ANB3
        001010 = ANB2
        001001 = ANB1
        001000 = ANB0
        000111 = ANA7
        000110 = ANA6
        000101 = ANA5
        000100 = ANA4
        000011 = ANA3
        000010 = ANA2
        000001 = ANA1
        000000 = ANA0
     //CODIGO PARA SELECCIONAR HACER LECTURA ANALOGICA 
        ADPCH=0b001010;//SELECCION DE CANAL ANB2
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc=adc<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc=adc+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        v5=adc*5.0/1023.0;//CONVERSION   
        __delay_ms(10);
     */
    ADCON0bits.ADON=1;//PRENDER ADC
    ADCON0bits.ADCONT=0;//Operacion normal
    ADCON0bits.ADCS=1; //Clock sourde=FCR
    ADCON0bits.ADFRM=1;//Justificacion derecha
    ADREFbits.ADNREF=0;//Voltaje de referencia negativo = Vss
    ADREFbits.ADPREF=0b00;//Vref=Vdd
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACION PUERTOS PARA MOTORES SALIDAS PWM  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PORTB=0; //LIMPA
    ANSELB=0b11111111; //PUERTO B COMO ANALOGICAS
    TRISB=0b11111111; //PUERTO B COMO ENTRADA >>>>ES para que no de senales al inicio malas
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>TMR2
    T2CLKCON=0b0001;// CS=FOSC/4
    T2CONbits.ON=1; //ENCENDER TIMER2
    T2CONbits.OUTPS=0; //POSTESCALER 1:1
    T2CONbits.CKPS=0b100; //PRESCALER 1:16
    PR2=255; //FRECUENCIA DE 1.95 KHZ
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACIONES DEL PWM 1 DERECHA DEL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    RB0PPS=0x09; //MODULO CCP1 SALDRA POR RB0 >>>PARA MOTOR1 DELANTE
    //RB1PPS=0x09; //MODULO CCP1 SALDRA POR RB1 >>>PARA MOTOR1 ATRAZ
    //RB6PPS=0x09;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CCP1
    CCP1CONbits.EN=1; //HABILITA  EL MODULO CCP1
    CCP1CONbits.FMT=0; //ALENEACION A LA DERECHA CCPR1H, L
    CCP1CONbits.MODE=0b1111; //MODO PWM
    CCPTMRS0bits.C1TSEL=0b01; //timer2 CCP1
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACIONES DEL PWM 2 DER ATRAZ <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    RB1PPS=0x0A; //MODULO CCP2 SALDRA POR RB2 >>>PARA MOTOR2 DELANTE >>>>>>>> CONFIGURACIONES EN LA PAGINA 240
    //RB3PPS=0x0A; //MODULO CCP2 SALDRA POR RB3 >>>PARA MOTOR2 ATRA
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CCP2
    CCP2CONbits.EN=1; //HABILITA  EL MODULO CCP2
    CCP2CONbits.FMT=0; //ALENEACION A LA DERECHA CCPR1H, L
    CCP2CONbits.MODE=0b1111; //MODO PWM
    CCPTMRS0bits.C2TSEL=0b01; //timer2 CCP1 >>Pagina 447 
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACIONES DEL PWM 3 IZQ DEL  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    RB2PPS=0x0B; //MODULO CCP2 SALDRA POR RB2 >>>PARA MOTOR2 DELANTE >>>>>>>> CONFIGURACIONES EN LA PAGINA 240
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CCP3
    CCP3CONbits.EN=1; //HABILITA  EL MODULO CCP3
    CCP3CONbits.FMT=0; //ALENEACION A LA DERECHA CCPR1H, L
    CCP3CONbits.MODE=0b1111; //MODO PWM
    CCPTMRS0bits.C3TSEL=0b01; //timer2 CCP1 >>Pagina 447 
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACIONES DEL PWM 4 IZQ ATRAZ  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    RB3PPS=0x0C; //MODULO CCP2 SALDRA POR RB2 >>>PARA MOTOR2 DELANTE >>>>>>>> CONFIGURACIONES EN LA PAGINA 240
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CCP4
    CCP4CONbits.EN=1; //HABILITA  EL MODULO CCP4
    CCP4CONbits.FMT=0; //ALENEACION A LA DERECHA CCPR1H, L
    CCP4CONbits.MODE=0b1111; //MODO PWM
    CCPTMRS0bits.C4TSEL=0b01; //timer2 CCP1 >>Pagina 447 
    
    /*
     CCP1
CCP2 CCP2
CCP3 CCP3
CCP4 CCP4
CCP5 CCP5
     */
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Iniciamos con los motores delanteros encendidos
    mderdel=0;//para encender del motor con el pwm se tiene que declarar el pin como salida
    mderatraz=1;
    mizqdel=0;
    mizqatraz=1;
    CCPR1=200;
    CCPR2=0;
    CCPR3=200;
    CCPR4=0;
    
    __delay_ms(1000);
    while(1){
        geterror();
        formula();
        errorant=error;
        //__delay_ms(10);
    }
    return (EXIT_SUCCESS);
}

