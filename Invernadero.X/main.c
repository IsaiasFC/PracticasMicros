/*
 * File:   main.c
 * Author: Isaias Flores Cabrera
 *
 * Created on March 25, 2019, 8:01 PM
 * Proyecto inverndadero control
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"
#include <math.h>
#define foco1 LATAbits.LATA1
#define ledon LATAbits.LATA0
#define ventilador LATDbits.LATD3
#define puertaAbrir LATDbits.LATD0
#define puertaCerrar LATDbits.LATD1
#define finalcarreraAbrir PORTDbits.RD2
#define finalcarreraCerrar PORTCbits.RC7
#define botonAC PORTCbits.RC6
int auxboton=0;
int angulo=0,t,c=1; //La variable angulo es para saber a que angulo se tiene que disparar el triac, t es para almacenar el tiempo calculado
                     // dependiendo del cruce por cero, C es el contador para el ciclo while dentro del metodo retardo
                     //El valor maximo del angulo esta entre 113-114
unsigned char buffer1[16],buffer2[16];// vecctor para desplegar las leyendas en la LCD
int adc1,adc2;//Variable usada para la lectura del potenciometro
int temperatura=24;// temperatura inicial para los calculos de la temperatura con el termistor
int energia=0; //Variable envianda por bluetooth para saber que porcentaje de energia se esta inyectando al sistema
int referencia;//Variable para almacenar la referencia a la que queremos que llegue el sistema

//Variables para el termistor
float vm;
float rntc=0.0;
float raux=10000.0;
float vcc=5.0;
float tkelvin=0.0;
float r0=10000.0;
float beta=3977.0;
float temp0=298.0;

int limite=112;//Valor maximo del angulo de disparo del triac
int auxcodigo;//Variable auxiliar que se usa para almacenar el codigo ascci de cada numero del 1 al 9, es usada en el metodo codigo
int contadorenviar=1;//Contador para saber cada que tiempo enviar los datos por bluetooth
//Variables para el PID
int error,P,U,Uant,ZM=12,T=5;//Variables para el algoritmo del PID
//float Kp=1.1807,Ti=15.452,I,Iant=0; //maso
//float Kp=2.1587,Ti=59.171,I,Iant=0;
float Kp=2.4692,Ti=55.2486,I,Iant=0;//Ganancias calculadas en matlab
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Metodo para mandar numeros por bluetoth<<<<<<<<<<<<<<<<<<<
int codigo(int num){
        switch(num){
            case 0:
                auxcodigo=48;
                break;
            case 1:
                auxcodigo=49;
                break;
            case 2:
                auxcodigo=50;
                break;
            case 3:
                auxcodigo=51;
                break;
            case 4:
                auxcodigo=52;
                break;
            case 5:
                auxcodigo=53;
                break;
            case 6:
                auxcodigo=54;
                break;
            case 7:
                auxcodigo=55;
                break;
            case 8:
                auxcodigo=56;
                break;
            case 9:
                auxcodigo=57;
                break;
        } 
        return auxcodigo;
        
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Fin de metodo para mandar numeros por bluetoth><<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Lectura de la referencia <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void leerref(){
        ADPCH=0b010101;//SELECCION DE CANAL C5
        
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc1=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc1=adc1<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc1=adc1+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        referencia=adc1*99.0/1024.0;//CONVERSION
       // angulo=adc1*112.0/1024.0;//CONVERSION
        //__delay_ms(10);
        
        //para temperatura
        ADPCH=0b010100;//SELECCION DE CANAL C4
        __delay_us(20);//ESPERAR A QUE SE CARGUE EL CAPACITOR DEL CONVERTIDO ADC
        ADCON0bits.ADGO=1;//Inicia la conversion
        while(ADCON0bits.ADGO);//Esperar a que terimine la conversion
        adc2=ADRESH;//PRIMEROS 2 BITS 0000000000000011
        adc2=adc2<<8;//RECORRE LOS 2 BITS A LA IZQUIERDA 8 POSICIONES 0000001100000000
        adc2=adc2+ADRESL;//SUMA LOS 8 BITS FALTANTES 0000001111111111;
        vm=adc2*5.0/1024.0;//CONVERSION
        
        //temperatura=(int)(vm*100);
         rntc=raux/((vcc/vm)-1);
         tkelvin=1/(((log(rntc/r0))/(beta))+(1/temp0));
         temperatura=((int)tkelvin-273);
         
       // __delay_ms(10);
        
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Metodo retardo <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void retardo(int to){
    to=to+10;
    while(c<=to){ //se hara el retardo hasta que c llegue al valor de to
    //__delay_ms(0.1);//retardo de un mili
        __delay_us(100);//retardo de 100 micros o 01.ms
    c++; // c incrementa en una unidad 
    }
    c=1; // regresamos c al valor inicial
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Interrupcion <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void __interrupt () interrupcio(void){
    if(IOCBFbits.IOCBF0==1){
        angulo=U;
        energia=(angulo*100)/limite;
        angulo=limite-angulo;
        t=(int)((angulo*83)/180);// regla de 3 para obtener el tiempo en que se dispara el triac
        retardo(t);//llamamos al metodo retardo y le pasamos el tiempo calculado para que dependiendo del angulo de disparo espere el tiempo necesario para activar el foco 
        foco1=1;//encendemos el foco
        __delay_ms(1);//mantenemos el pulso 1 ms
        foco1=0;//apagamos el foco
        IOCBF=0;// Limpiamos la badera de B0
    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Fin interrupcion <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void main(void) {
    //Configuracion del oscilador
    OSCFRQbits.HFFRQ=0b110; //Selecionamos la oscilacion interna
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PULL UPS PARA FINALES DE CARRERA
    WPUDbits.WPUD2=1;
    WPUCbits.WPUC7=1;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Configuracion de puertos I/Os
    PORTB=0;//Limpiamos el puerto B
    ANSELBbits.ANSB0=0;//Puerto B0 como digital
    TRISBbits.TRISB0=1;//Puerto B0 como entrada
    ANSELBbits.ANSB1=0;//Puerto B1 como digital
    TRISBbits.TRISB1=1;//Puerto B1 como entrada para el RX
    RB2PPS=0x10;//Puerto B2 como TX 
    
    PORTA=0;//limpiamos el puerto A
    ANSELAbits.ANSA0=0;//Puerto A0 como digital
    TRISAbits.TRISA0=0;//Puerto A0 como salida
    ANSELAbits.ANSA1=0;//Puerto A1 como digital
    TRISAbits.TRISA1=0;//Puerto A1 como salida
    ANSELAbits.ANSA6=0;//Puerto A6 como digital
    ANSELAbits.ANSA7=0;//Puerto A7 como digital
    PORTC=0;//Limpiamos el puerto C
    ANSELCbits.ANSC0=0;//Puerto C0 como digital
    ANSELCbits.ANSC1=0;//Puerto C1 como digital
    ANSELCbits.ANSC2=0;//Puerto C2 como digital
    ANSELCbits.ANSC3=0;//Puerto C3 como digital
    ANSELCbits.ANSC4=1;//Puerto C4 como Analogico
    ANSELCbits.ANSC5=1;//Puerto C5 como Analogico
    TRISCbits.TRISC4=1;//Puerto C4 como entrada para temperatura
    TRISCbits.TRISC5=1;//Puerto C5 como entrada para referencia
    ANSELCbits.ANSC6=0;//Puerto C6 como digital
    TRISCbits.TRISC6=1;//Puerto C6 como entrada para el boton de apertura y cierre de la puerta
    ANSELCbits.ANSC7=0;//Puerto C7 como digital
    TRISCbits.TRISC7=1;////Puerto C7 como entrada para finalcarreraCerrar
    PORTD=0;//limpiamos el puerto D
    ANSELDbits.ANSD0=0;// D0 digital para enceder el puente h ABRIR
    TRISDbits.TRISD0=0;// D0 Salida
    ANSELDbits.ANSD1=0;// D1 digital para encender el puente h CERRAR
    TRISDbits.TRISD1=0;// D1 Salida
    ANSELDbits.ANSD2=0;// D2 digital para finalcarreraAbrir
    TRISDbits.TRISD2=1;// D2 Entrada
    ANSELDbits.ANSD3=0;// D3 digital para encender el ventilador
    TRISDbits.TRISD3=0;// D3 Salida
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Fin de configuraciones de I/Os
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Configuracion de Tx y Rx
    RC1STAbits.SPEN=1; //HABILITA EL PUERTO SERIE
    TX1STAbits.TXEN=1; //HABILITA LA TRANSMISION
    //RC1STAbits.CREN=1; //HABILITA LA RECEPCION CONTINUA DE DATOS
    TX1STAbits.SYNC=0; //MODO ASINCRONO
    //Configuracion de baudrate
    BAUDCONbits.BRG16=0; //8 BITS
    TX1STAbits.BRGH=0; //low speed BAJA VELOCIDAD <<PAJINA 565
    SPBRG=51; //VELOCDAD DE 9600 PAJINA 571
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Fin configuracion Rx y Tx
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Configuraciones para ADC
    ADCON0bits.ADON=1;//PRENDER ADC
    ADCON0bits.ADCONT=0;//Operacion normal
    ADCON0bits.ADCS=1; //Clock sourde=FCR
    ADCON0bits.ADFRM=1;//Justificacion derecha
    ADREFbits.ADNREF=0;//Voltaje de referencia negativo = Vss
    ADREFbits.ADPREF=0b00;//Vref=Vdd
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Fin configuracion ADC
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Inicio de configuraciones de Interrupcion Externa
    IOCBNbits.IOCBN0=1;//Flanco de bajada en B0
    IOCBF=0;//Limpia las banderas individuales en IOC PORTB
    PIR0bits.IOCIF=0;//LIMPIA BADERA GENERAL IOC
    PIE0bits.IOCIE=1; //Habilita la interrupcion en IOC
    INTCONbits.GIE=1; // Habilita interrupcion global
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Fin configuraciones Externas
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Iniciamos la LCD
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Fin Inicio LCD
    //###PRENDEMOS EL LED DE ENCENDIDO
    ledon=1;
    U=U+ZM;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Ciclo Infinito
    while(1){
        //angulo=112 toda la potencia del foco, angulo=0 foco apagado
        leerref();
        error=referencia-temperatura;
        P=Kp*error;
        if(Uant>limite){I=Iant;}else{I=Iant+(Kp*T*error)/(Ti);}//anti wind up
        U=P+I+ZM;
        //angulo=U;
        if(U>limite){U=limite;}else if(U<0){U=0;}//limitar la salida
        Iant=I;
        Uant=U;
        
        
        //Lcd_Cmd(LCD_CLEAR);
        sprintf(buffer1,"An=%03d Rf=%02d",angulo,referencia);
        Lcd_Out2(1,0,buffer1);
        sprintf(buffer2,"T=%03d U=%03d",temperatura, U);
        Lcd_Out2(2,0,buffer2);
        if(botonAC==1){
            if(auxboton==0){
            //ABRIR PUERTA
                while(auxboton==0){
                    puertaAbrir=1;
                    if(finalcarreraAbrir==0){auxboton=1;}
                }
                puertaAbrir=0;
                
            }else{
            //CERRAR PUERTA
                while(auxboton==1){
                    puertaCerrar=1;
                    if(finalcarreraCerrar==0){auxboton=0;}
                }
                puertaCerrar=0;
                
            }
        }
        
        if(contadorenviar==30){
        //enviar temperatura por bluetooth
            if(temperatura<10 && temperatura>=0){
             TX1REG=codigo(0);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(0);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(temperatura);
             while(TXSTAbits.TRMT==0);
             //envio de referencia
             TX1REG=codigo(referencia/100);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(referencia/10);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(referencia-((referencia/10)*10));
             while(TXSTAbits.TRMT==0);
             //envio de energia
             TX1REG=codigo(energia/100);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(energia/10);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(energia-((energia/10)*10));
             while(TXSTAbits.TRMT==0);
             //envio de ~ para saber el final de la cadena enviada
             TX1REG=126;//="~"
         }else if(temperatura>=10 && temperatura<100){
             TX1REG=codigo(0);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(temperatura/10);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(temperatura-((temperatura/10)*10));
             while(TXSTAbits.TRMT==0);
             //envio de referencia
             TX1REG=codigo(referencia/100);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(referencia/10);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(referencia-((referencia/10)*10));
             while(TXSTAbits.TRMT==0);
               //envio de energia
           //  TX1REG=codigo(energia/100);
             TX1REG=codigo(energia/100);
             while(TXSTAbits.TRMT==0);
            // TX1REG=codigo(energia/10);
             TX1REG=codigo(((energia-((energia/100)*100))/10));
             while(TXSTAbits.TRMT==0);
             //TX1REG=codigo(energia-((energia/10)*10));
             TX1REG=codigo((energia-(((energia/100)*100)+(((energia-((energia/100)*100))/10)*10))));
             while(TXSTAbits.TRMT==0);
             //envio de ~ para saber el final de la cadena enviada
             TX1REG=126;//="~"
             
         }else if(temperatura>=100 && temperatura<1000){
             TX1REG=codigo(temperatura/100);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(temperatura/10);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(temperatura-((temperatura/10)*10));
             while(TXSTAbits.TRMT==0);
             //envio de referencia
             TX1REG=codigo(referencia/100);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(referencia/10);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(referencia-((referencia/10)*10));
             while(TXSTAbits.TRMT==0);
               //envio de energia
             TX1REG=codigo(energia/100);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(energia/10);
             while(TXSTAbits.TRMT==0);
             TX1REG=codigo(energia-((energia/10)*10));
             while(TXSTAbits.TRMT==0);
             //envio de ~ para saber el final de la cadena enviada
             TX1REG=126;//="~"
         }
         contadorenviar=0;   
        //fin envio temperatura    
        }else{contadorenviar=contadorenviar+1;}
        __delay_ms(10);
        
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Fin ciclo infinito
    return;
}
