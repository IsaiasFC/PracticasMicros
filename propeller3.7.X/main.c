/*
 * File:   main.c
 * Author: marck antony
 *
 * Created on 7 de octubre de 2018, 06:53 PM
 */


#include <xc.h>
#include <pic16f18877.h>
#include "config.h"
#define _XTAL_FREQ 32000000

//** DEFINIMOS LAS ETIQUETAS DE CADA LED COMO SALIDA
//**PARA LOS LEDS DE LA BARRA VERTICAL

#define led1 PORTCbits.RC1  
#define led2 PORTAbits.RA0 //**EN LA BARRA ESTE ORDEN ESTA DEFINIDO DE ABAJO HACIA ARRIVA
#define led3 PORTAbits.RA1
#define led4 PORTAbits.RA2
#define led5 PORTAbits.RA3
#define led6 PORTAbits.RA4
#define led7 PORTAbits.RA5
#define led8 PORTAbits.RA7
#define led9 PORTAbits.RA6
#define led10 PORTCbits.RC2

//**PARA LOS LEDS DE LA BARRA HORIZONTAL DEL PROPELL
//**EL ORDEN ESTA DEFINIDO DEL PRIMER LED A PARTIR DE LA PROTO HACIA ADELANTE

#define led01 PORTDbits.RD0
#define led02 PORTDbits.RD1
#define led03 PORTDbits.RD2
#define led04 PORTDbits.RD3
#define led05 PORTDbits.RD4
#define led06 PORTDbits.RD5
#define led07 PORTDbits.RD6
#define led08 PORTDbits.RD7
#define led09 PORTCbits.RC0

//**PARA EL SENDOR INFRERROJO
#define salida PORTCbits.RC3
#define entrada LATCbits.LATC4
//**VARIABLES A UTILIZAR
//int tiempo;
//int aux, timeAng;
int cmils=0,cseg=0, cmin=24, chr=9;
int unidades=0, decenas=0;
void __interrupt() interrupcion(void){
    if(cmils==16){
        cseg=cseg+1;
        cmils=0;
    }else{
        cmils=cmils+1;
    }
    
    if(cseg>58){
        cmin=cmin+1;
        cseg=0;
    }
    
    if(cmin>59){
        chr=chr+1;
        cmin=0;
    }
    
    if(chr>12){
        chr=0;
    }
    
    
    
    TMR1=536;//precarga
    PIR4bits.TMR1IF=0; //**LIMPIA BANDERA DEL TIMMER1 PAJ 148
    
}
//**CREACION DE UN METODO PARA APAGAR TODOS LOS LEDS
void off (){
    PORTA=0b00000000;//**APAGAMOS TODOS LOS PUERTOS DEL PUERTO B 
}
//**METODO PARA ENCENDER
void on(){
    PORTA=0b11111111;
}
//**METODO PARA ANGULOS
void timeAngulo(int time){
    
__delay_ms(time);
    
}
//**METODO PARA DELAYS DE ENCENDIDO DE LEDS PARA IMPRESION DE NUMEROS
void espera (){
    __delay_us(800);
}
//**METODOS DE IMPRESION DE NUMEROS
//**CORAXON METODO
void corazon (){
    LATCbits.LATC0=1;
    PORTD=0b01110001;
    espera();
    off();
    PORTD=0b11111001;
    espera();
    off();
    PORTD=0b11111101;
    espera();
    off();
    PORTD=0b01111111;
    espera();
    PORTD=0b00111111;
    espera();
    off();
    PORTD=0b01111110;
    espera();
    off();
    PORTD=0b11111101;
    espera();
    off();
    PORTD=0b11111001;
    espera();
    PORTD=0b01110001;
    espera();
    off();
    espera();


}
void leyenda(void){
    LATCbits.LATC0=0;
    PORTD=0b01111000;
    espera();
    off();
    LATCbits.LATC0=0;
    PORTD=0b11111100;
    espera();
    off();
    LATCbits.LATC0=1;
    PORTD=0b11111110;
    espera();
    off();
    LATCbits.LATC0=1;
    PORTD=0b11101110;
    espera();
    off();
    LATCbits.LATC0=1;
    PORTD=0b11000110;
    espera();
    off();
    LATCbits.LATC0=1;
    PORTD=0b10000010;
    espera();
    off();
    espera();
}
//**NUMERO 0
void cero (){
    PORTA=0b10111110;
    espera();
    off();
    PORTA=0b01000001;
    espera();
    off();
    PORTA=0b01000001;
    espera();
    off();
    PORTA=0b10111110;
    espera();
    off();
    espera();
}
//**NUMERO 1
void uno (){
    PORTA=0b00000001;
       espera();
       off();
       PORTA=0b11111111;
       espera();
       off();
       PORTA=0b01000001;
       espera();
       off();
       espera();
}
//**NUMERO 2
void dos (){
    PORTA=0b10100111;
    espera();
    off();
    PORTA=0b01001001;
    espera();
    off();
    PORTA=0b01010001;
    espera();
    off();
    PORTA=0b10100001;
    espera();
    off();
    espera();
}
//**NUMERO 3
void tres (){
    PORTA=0b01000010;
    espera();
    off();
    PORTA=0b01000001;
    espera();
    off();
    PORTA=0b01010001;
    espera();
    off();
    PORTA=0b01110010;
    espera();
    off();
    PORTA=0b11001100;
    espera();
    off();
    espera();
}
//**NUMERO 4
void cuatro (){
    PORTA=0b11110000;
    espera();
    off();
    PORTA=0b00010000;
    espera();
    off();
    PORTA=0b00010000;
    espera();
    off();
    PORTA=0b11111111;
    espera();
    off();
    espera();
}
//**NUMERO 5
void cinco (){
    PORTA=0b11110011;
    espera();
    off();
    PORTA=0b01010001;
    espera();
    off();
    PORTA=0b01010001;
    espera();
    off();
    PORTA=0b01001110;
    espera();
    off();
    espera();
}
//**NUMERO 6
void seis (){
    PORTA=0b00111110;
    espera();
    off();
    PORTA=0b10010001;
    espera();
    off();
    PORTA=0b01010001;
    espera();
    off();
    PORTA=0b01001110;
    espera();
    off();
    espera();
}
//**NUMERO 7
void siete (){
    PORTA=0b01000000;
    espera();
    off();
    PORTA=0b01010000;
    espera();
    off();
    PORTA=0b01010000;
    espera();
    off();
    PORTA=0b11111111;
    espera();
    off();
    espera();
}
//**NUMERO 8
void ocho (){
    PORTA=0b10101110;
    espera();
    off();
    PORTA=0b01010001;
    espera();
    off();
    PORTA=0b01010001;
    espera();
    off();
    PORTA=0b10101110;
    espera();
    off();
    espera();
}
//**NUMERO 9
void nueve (){
    PORTA=0b10100001;
    espera();
    off();
    PORTA=0b01010010;
    espera();
    off();
    PORTA=0b01010100;
    espera();
    off();
    PORTA=0b10111000;
    espera();
    off();
    espera();
}
//**METODO PARA PUNTOS DE SEPARACION
void puntos (){
    PORTA=0b10101100;
    espera();
    off();
    PORTA=0b10101100;
    espera();
    off();
    
}
//**METODO PARA VARIABLE NUMERO
void numero (int n){
    switch(n){
        case 0:
            cero();
            break;
        case 1:
            uno();
            break;
        case 2:
            dos();
            break;
        case 3:
            tres();
            break;
        case 4:
            cuatro();
            break;
        case 5:
            cinco();
            break;
        case 6:
            seis();
            break;
        case 7:
            siete();
            break;
        case 8:
            ocho();
            break;
        case 9:
            nueve();
            break;
    }
              
              

}

void impresiont(int hr, int min, int seg){
    //>>>>>>>>>>>>>>>>>>>>>>>>>> imprimir horas
    if(hr<10){
        numero(hr);
        espera();
        puntos();
    }else{
        unidades=hr-10;
        decenas=hr/10;
        numero(decenas);
        espera();
        numero(unidades);
        espera();
        puntos();
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>> imprimir minuros
    if(min<10){
        cero();
        espera();
        numero(min);
        espera();
        puntos();
    }else{
        unidades=min-(min/10)*10;
        decenas=min/10;
        numero(decenas);
        espera();
        numero(unidades);
        espera();
        puntos();
    }
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>> imprimir segundos
    if(seg<10){
        cero();
        espera();
        numero(seg);
        espera();
        //puntos();
    }else{
        unidades=seg-(seg/10)*10;
        decenas=seg/10;
        numero(decenas);
        espera();
        numero(unidades);
        espera();
        //puntos();
    }
    
}
void main(void) {
    //**OSCILADOR
    OSCFRQbits.HFFRQ=0b110; //**velocidad del oscilador
    
    //**PUERTOS A UTILIZAR
    //**A
    PORTA=0; //**LIMPIAMOS PUERTOS
    TRISA=0; //**COMO SALIDAS
    ANSELA=0; //**COMO DIGITALES
    //**D
    PORTD=0; //**LIMPIAMOS PUERTOS
    TRISD=0; //**SALIDAS
    ANSELD=0; //**DIGITALES
    //**C
    PORTC=0; //**LIMPIAMOS PUERTOS C
    TRISC=0b00010000; //**SALIDAS
    ANSELC=0; //**DIGITALES
    
    //**CONFIGURACION DEL TIMMER
    //**PAGINA 411
    T1CON=0b00110110;
    //**PREESCALER DE 4
    //**NO SINCRONIZADO
    T1CLKbits.CS=0b0001; //**Fosc/4
    
    //**CONFIGURACION DE UNTERRUPCIONES DE TIMMER
    PIE4bits.TMR1IE=1; //**INTERRUPCION DE TIMMER1 HABILITADA PAJ 139
    PIR4bits.TMR1IF=0; //**LIMPIA BANDERA DEL TIMMER1 PAJ 148
    INTCONbits.GIE=1; //**INTERRUPCION GLOBAL HABILITADA
    INTCONbits.PEIE=1; //**INTERRUPCION POR PERIFERICO HABILITADA
    
    TMR1=536; //**PRECARGA se va a desbordar cada 64 milis
    
    T1CONbits.ON=1; //**ENCENDIDO Y COMIENZO DEL CONTEO DEL TIMMER1
    int v=235;
    //**ciclo infinito
    while(1){
      /* cinco();
       espera();
       seis();
       espera();
       corazon();
       espera();
       __delay_ms(15);*/
        //__delay_ms(150);
        impresiont(chr,cmin,cseg);
        leyenda();
        //-corazon();
        /*switch(cseg){
            case 10:
                v=v+5;
                break;
            case 20:
                v=v+5;
                break;
            case 30:
                v=v+5;
                break;
            case 40:
                v=v+5;
                break;
            case 50:
                v=v+5;
                break;
            case 60:
                v=v+5;
                break;
            default:
                break;
        }*/
        
        __delay_ms(45);
        
    }

    return;
}
