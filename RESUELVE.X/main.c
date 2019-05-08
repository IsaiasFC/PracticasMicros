/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 30 de octubre de 2018, 7:54
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <xc.h>

#define mderdel LATBbits.LATB0 //Motor DERECHO DELANTE
#define mderatraz LATBbits.LATB1 //Motor DERECHO ATRAZ

#define mizqdel LATBbits.LATB2 //MOTOR IZQUIERDO DELANTE
#define mizqatraz LATBbits.LATB3 //MOTOR IZQUIERDO ATRAZ

#define _XTAL_FREQ 32000000
#define trig1 LATAbits.LATA0
#define echo1 PORTAbits.RA1

#define trig2 LATAbits.LATA2
#define echo2 PORTAbits.RA3

#define trig3 LATAbits.LATA4
#define echo3 PORTAbits.RA5

double tiempo1=0,tiempo2=0,tiempo3=0;
double distancia1=0,distancia2=0,distancia3=0;
int calibracion=1;

int error=0, errorant=0;
double kp=0.446,kd=0.246,ki=60;
int velocidad=700;

void geterror(void){
    //>>>>>>>>>>>>>>>>>>>>>>>>> SENSOR 1 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            TMR1=0;
            trig1=1;
            __delay_us(10);
            trig1=0;
            while(echo1==0);
            T1CONbits.ON=1; //Inicia el TMR1
            while(echo1);
            T1CONbits.ON=0; //Apaga el TMR1
            tiempo1=((((double)TMR1))/2000000);
            distancia1=(int)((34000*tiempo1)/2)-calibracion;
    //>>>>>>>>>>>>>>>>>>>>>>>>> SENSOR 2 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            TMR1=0;
            trig2=1;
            __delay_us(10);
            trig2=0;
            while(echo2==0);
            T1CONbits.ON=1; //Inicia el TMR1
            while(echo2);
            T1CONbits.ON=0; //Apaga el TMR1
            tiempo2=((((double)TMR1))/2000000);
            distancia2=(int)((34000*tiempo2)/2)-calibracion;            
    //>>>>>>>>>>>>>>>>>>>>>>>>> SENSOR 3 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            TMR1=0;
            trig3=1;
            __delay_us(10);
            trig3=0;
            while(echo3==0);
            T1CONbits.ON=1; //Inicia el TMR1
            while(echo3);
            T1CONbits.ON=0; //Apaga el TMR1
            tiempo3=((((double)TMR1))/2000000);
            distancia3=(int)((34000*tiempo3)/2)-calibracion;
            
    //>>>>>>>>>>>>>>>>>>>>>>>>> CALCULO DE ERROR >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            error=(0*distancia1+1000*distancia2+2000*distancia3)/(distancia1+distancia2+distancia3);
            error=error-1000;
}
void formula(void){
    if(distancia1==distancia2 && distancia2==distancia3){
        //IZQUIERDA
        mderdel=1;
        mderatraz=0;
        mizqdel=0;
        mizqatraz=1;
        //CCPR1=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
        //CCPR2=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
    }else{
    if(error<-100){
        //IZQUIERDA
        mderdel=1;
        mderatraz=0;
        mizqdel=0;
        mizqatraz=1;
        //CCPR1=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
        //CCPR2=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
    }else if(error>100){
        //DERECHA
        mderdel=0;
        mderatraz=1;
        mizqdel=1;
        mizqatraz=0;
        //CCPR1=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
        //CCPR2=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
    }else {
        
        mderdel=1;
        mderatraz=0;
        mizqdel=1;
        mizqatraz=0;
        //CCPR1=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
        //CCPR2=velocidad-(int)((kp*(double)error)+kd*((double)error-(double)errorant));
        /*if(error<0){
            CCPR1=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
            CCPR2=velocidad+(int)((-1)*((kp*(double)error)+kd*((double)error-(double)errorant)));
        }else{
            CCPR1=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
            CCPR2=velocidad+(int)((kp*(double)error)+kd*((double)error-(double)errorant));
        }*/
        //__delay_ms(10);
    }
}
}
void __interrupt () interrupcion(void){
    
    PIR4bits.TMR1IF=0; //Limpia bandera de timer 1
     //LIMPIA LA BANDERA
}
int main(int argc, char** argv) {
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< puertos para sensor >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    PORTA=0;
    ANSELA=0;
    TRISAbits.TRISA0=0; //salida   >>>>>>>>>>SENSOR1
    TRISAbits.TRISA1=1; //entrada
    
    TRISAbits.TRISA2=0; //salida  >>>>>>>>>>>>>SENSOR2
    TRISAbits.TRISA3=1; //entrada
    
    TRISAbits.TRISA4=0; //salida >>>>>>>>>>>>>>>SENSOR3
    TRISAbits.TRISA5=1; //entrada
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CONFIGURACION PUERTOS PARA MOTORES SALIDAS PWM  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PORTB=0; //LIMPA
    ANSELB=0; //PUERTO B COMO ANALOGICAS
    TRISB=0; //PUERTO B COMO ENTRADA >>>>ES para que no de senales al inicio malas
    
    //>>>>>>>>>>>>>>>>>>>>> Configuracion de interrupciones <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    PIR4bits.TMR1IF=0; //Limpia bandera de timer 1
    PIE4bits.TMR1IE=1;//Habilita interrupcion por timer 1
    INTCONbits.GIE=1; //Habilita interrupcion global
    INTCONbits.PEIE=1; // habilita interrupcion por periferico
    PIE4bits.TMR1IE=1;
     //<<<<<<<<<<<<<<<<<<<<<<<<<<<< CONFIGURACION DE TMR1 >>>>>>>>>>>>>>>>>>>>>>>
    T1CONbits.CKPS=0b10; //PREESCALER    
    T1CLKbits.CS=0b0001;//Frecuencia FOCS/4=0001 
    T1CONbits.nSYNC=1; //NO SINCRONIZADO
    
    mderdel=1;//para encender del motor con el pwm se tiene que declarar el pin como salida
    mderatraz=0;
    
    mizqdel=1;
    mizqatraz=0;
    __delay_ms(1000);
    while(1){
        geterror();
        formula();
        errorant=error;
        //__delay_ms(10);
    }
    
    
    return (EXIT_SUCCESS);
}

