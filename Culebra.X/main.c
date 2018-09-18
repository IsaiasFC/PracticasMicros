/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 8 de septiembre de 2018, 16:39
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <pic16f18877.h>

#define _XTAL_FREQ 32000000

#define barriba PORTDbits.RD6
#define babajo PORTDbits.RD5
#define bderecha PORTDbits.RD4
#define bizquierda PORTDbits.RD7

    int letra[8];
    int cuerpo=3;
    int culebrafila=2; //XP          
    int culebracolumna=2;   //YP
    int comidafila=0;           
    int comidacolumna=0;
    int direccion=1; 
    int poscabfila[64]; //x=fila
    int poscabcolumna[64]; //y=columna
    int movfilas [8]={0b01111111,0b10111111,0b11011111,0b11101111,0b11110111,0b11111011,0b11111101,0b11111110};
    //7 6 5 4 3 2 1 0
    int movcolumnas[8]={0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
   
    

void mostrarletra(int f [], int c[]){
    //Inicia ciclo para mostrar la la letra 
        for(int cambio=0;cambio<5;cambio++){
        //inicio para pintar matriz
        for(int veces=0;veces<50;veces++){
        for(int b=0;b<8;b++){
            PORTA=f[b];
            PORTC=c[b];
            __delay_ms(1);
        }
    } //fin de pintado de matriz
        __delay_ms(10);
        }//fin ciclo para mostrar la culebra en su posicion 0.5 segundos   
        return;
}

int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    PORTC=0;
    PORTD=0;
    PORTA=0;
    ANSELA=0b00000000;
    ANSELD=0b00000000;
    ANSELC=0b00000000;
    
    TRISA=0;
    TRISC=0;
    TRISD=0b11110000;
    WPUDbits.WPUD7=1;
    WPUDbits.WPUD6=1;
    WPUDbits.WPUD5=1;
    WPUDbits.WPUD4=1;
    
    
    
   //poscicion de la comida aleatoria
    //x=fila y=columna
    //numero = rand() % (N+1);
    
    //srand (TMR0); // Done once
    comidafila = rand() % 7 + 0;         
    comidacolumna= rand() % 7 + 0; 
    while(1){
        ////////////////////////////////////////////////////////////////////inicio ciclo for 10
        for(int cuenta=0;cuenta<10;cuenta++){
        //******a=1 arriba 	a=2 abajo	a=3 izquierda	a=4 derecha
    //verificacion boton abajo
        if(babajo==0){
            __delay_ms(250);
            if(direccion==1){
                direccion=1;
            }else{
                direccion=2;
            } 
        }
        
        //verificacion boton arriba
        if(barriba==0){
            __delay_ms(250);
            if(direccion==2){
                direccion=2;
            }else{
                direccion=1;
            } 
        }
        
        //verificacion boton derecha
        if(bderecha==0){
            __delay_ms(250);
            if(direccion==3){
                direccion=3;
            }else{
                direccion=4;
            } 
        }
        
        //verificacion boton izquierda
        if(bizquierda==0){
            __delay_ms(250);
            if(direccion==4){
                direccion=4;
            }else{
                direccion=3;
            } 
        }
        
        //POSICION INCIAL DE LA CULEBRA
        poscabfila[1]=movfilas[culebrafila];       
        poscabcolumna[1]=movcolumnas[culebracolumna];

        for(int i=cuerpo;i>=0;i--){//INICIO FOR PARA MOSTRAR CULEBRA Y COMIDA
            if(i==0){ 
                PORTC=movfilas[comidafila];
                PORTA=movcolumnas[comidacolumna];
                //if para verificar si come 
                if(comidafila==culebrafila && comidacolumna==culebrafila){
                    cuerpo=cuerpo+1;
                    comidafila = rand() % 7 + 0;         
                    comidacolumna= rand() % 7 + 0;
                    //se puede dar un retardo de un milisegundo y apagar matriz activando PORTC=0b11111111 o PORT=255;
                }
                __delay_ms(1);
                PORTC=0b11111111;
                
            }else{
                    //saber si la posicion de la cola es igual a la posicion de la cabeza
                    //X=FILA Y=COLUMNA
                    if(movfilas[culebrafila]==poscabfila[i+1] && movcolumnas[culebracolumna]==poscabcolumna[i+1]){
                        //letra={Ob00000000,0b01111110,0b01111110,0b01001110,0b01101110,0b01101110,0b01101110,0b00001100};//letra G
                        letra[0]=0b00000000;
                        letra[1]=0b01111110;
                        letra[2]=0b01111110;
                        letra[3]=0b01001110;
                        letra[4]=0b01101110;
                        letra[5]=0b01101110;
                        letra[6]=0b01101110;
                        letra[7]=0b00001100;
                        mostrarletra(letra,movcolumnas);
                       // letra={0b00000000,0b11100110,0b11100110,0b11100110,0b11100110,0b11100110,0b11100110,0b00000000};//letra A
                        //mostrarletra(letra,movcolumnas);
                        //letra={0b00000000,0b11111110,0b11111110,0b00000001,0b00000001,0b11111110,0b11111110,0b00000000};//letra M
                        //mostrarletra(letra,movcolumnas);
                        //letra={0b00000000,0b01100110,0b01100110,0b01100110,0b01100110,0b01100110,0b01100110,0b01100110};//letra E
                       // mostrarletra(letra,movcolumnas);
                        //letra={0b00000000,0b01111110,0b01111110,0b01111110,0b01111110,0b01111110,0b01111110,0b00000000};//letra O
                       // mostrarletra(letra,movcolumnas);
                        //letra={0b11111100,0b11110011,0b11001111,0b00111111,0b00111111,0b11001111,0b11110011,0b11111100};//letra v
                       // mostrarletra(letra,movcolumnas);
                        //letra={0b00000000,0b01100110,0b01100110,0b01100110,0b01100110,0b01100110,0b01100110,0b01100110};//letra E
                       // mostrarletra(letra,movcolumnas);
                        //letra={0b00000000,0b11110110,0b11110110,0b11100110,0b11010110,0b10110110,0b01110110,0b11110000};//letra R
                        //mostrarletra(letra,movcolumnas);
                        return;
                    }
                    
                    //MOSTRAR LA CULEBRA COMPLETA 
                    PORTC=poscabfila[i];              
                    PORTA=poscabcolumna[i];            
                    __delay_ms(1000);        
                    PORTC=255;
                
                }
        }//INICIO FOR PARA MOSTRAR CULEBRA Y COMIDA
       
        
        
        }
        
        /////////////////////////////////////////////////////////////////// fin ciclo for 10
        //inicio switch para cambio de direccion
        //X= FILA Y=COLUMNA
        switch(direccion){
            case 1:
            //ARRIBA
                culebracolumna=culebracolumna+1;
            break;
             case 2:
                 //ABAJO
                culebracolumna=culebracolumna-1;
                break;
            case 3:
                //IZQUIERDA
                //
                culebrafila=culebrafila-1;
                break;
            case 4:
                //DERECHA
                culebrafila=culebrafila+1;
                break;
            
        }//fin del switch
        if(culebrafila>7){
            culebrafila=0;
        }
        if(culebrafila<0){
            culebrafila=7;
        }
        if(culebracolumna>7){
            culebracolumna=0;
        }
        
        if(culebracolumna<0){
            culebracolumna=7;
        }
        
        for(int i=cuerpo;i>1;i--){
            poscabfila[i]=poscabfila[i-1];
            poscabcolumna[i]=poscabcolumna[i-1];
        }
        

    }//fin del whilw infinito
    return (EXIT_SUCCESS);
}



/*
 //Inicia ciclo para mostrar la culebra en su posicion 1 segundo
        for(int cambio=0;cambio<5;cambio++){
        //inicio para pintar matriz
        for(int veces=0;veces<50;veces++){
        for(int bits=0;bitsi<8;bits++){
            PORTA=movfilas[bits];
            PORTC=movcolumnas[bits];
            __delay_ms(1);
        }
    } //fin de pintado de matriz
        __delay_ms(10);
        }//fin ciclo para mostrar la culebra en su posicion 0.5 segundos        
        __delay_ms(10);
 
 */
