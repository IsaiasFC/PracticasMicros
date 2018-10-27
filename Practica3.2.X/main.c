/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 25 de septiembre de 2018, 18:35
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"

#define fila0 LATAbits.LATA4
#define fila1 LATAbits.LATA5
#define fila2 LATAbits.LATA6
#define fila3 LATAbits.LATA7

#define col0 PORTAbits.RA0
#define col1 PORTAbits.RA1
#define col2 PORTAbits.RA2
#define col3 PORTAbits.RA3

static int contin1=1;
static int contin2=1;
static int num1_int=0;
static int num2_int=0;
static int res_int=0;
static int operacion; //1= suma 2= resta
static char num1_char[16];
static char num2_char[16];
static char entrada[1];
static char resultado_char[16];
void resultado(char valor1[16], char valor2[16]){
    for(int i=0;i<=2;i++){
        if(i==0){num1_int=(valor1[i]-'0');num2_int=(valor2[i]-'0');}
        if(i==1){num1_int=num1_int+(valor1[i]-'0')*10;num2_int=num2_int+(valor2[i]-'0')*10; }
        if(i==2){num1_int=num1_int+(valor1[i]-'0')*100;num2_int=num2_int+(valor2[i]-'0')*100; }
    }
    if(operacion==1){
        res_int=num1_int+num2_int;
    }else if(operacion==1){
        res_int=num1_int-num2_int;
    }
    
    
}
void convertirnum1(char num[16]){
    for(int i=0;i<=2;i++){
        if(i==0){num1_int=(num[i]-'0');}
        if(i==1){num1_int=num1_int+(num[i]-'0')*10; }
        if(i==2){num1_int=num1_int+(num[i]-'0')*100;}
    }
}

void convertirnum2(char num2[16]){
    for(int i=0;i<=2;i++){
        if(i==0){num2_int=(num2[i]-'0');}
        if(i==1){num2_int=num2_int+(num2[i]-'0')*10; }
        if(i==2){num2_int=num2_int+(num2[i]-'0')*100;}
    }
}
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    PORTA=0;
    ANSELA=0;
    TRISA=0b00001111;
    WPUA=0b11111111;
    ANSELA=0;
    PORTD=0;
    PORTC=0;
    ANSELD=0;
    ANSELC=0;
    //Variable para imprimir en la lcd
    unsigned char buffer1[16],buffer2[16];
    //INICIAR Y LIMPIAR LCD
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    while(1){
        if(contin1<=3){
            fila0=1;fila1=1;fila2=1;fila3=1;
            fila0=0;
            if(col0==0){entrada[0]=1;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col1==0){entrada[0]=2;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col2==0){entrada[0]=3;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col3==0){entrada[0]="A";if(num1_char!=NULL){contin1=4;operacion=1; }}//operacion=1 SUMA
            fila0=1;
            fila1=0;
            if(col0==0){entrada[0]=4;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col1==0){entrada[0]=5;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col2==0){entrada[0]=6;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col3==0){entrada[0]="B";if(num1_char!=NULL){contin1=4;operacion=0; }}//operacion=0 RESTA
            fila1=1;
            fila2=0;
            if(col0==0){entrada[0]=7;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col1==0){entrada[0]=8;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col2==0){entrada[0]=9;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col3==0){entrada[0]="C";}
            fila2=1;
            fila3=0;
            if(col0==0){entrada[0]="*";strcat(num1_char,entrada);}
            if(col1==0){entrada[0]=0;strcat(num1_char,entrada); contin1++;convertirnum1(num1_char);}
            if(col2==0){entrada[0]="#";strcat(num1_char,entrada);}
            if(col3==0){entrada[0]="D";}
            fila3=1;
            __delay_ms(100);
        }else{
            if(contin2<=3){
                fila0=1;fila1=1;fila2=1;fila3=1;
                fila0=0;
                if(col0==0){entrada[0]=1;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col1==0){entrada[0]=2;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col2==0){entrada[0]=3;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col3==0){entrada[0]="A";}
                fila0=1;
                fila1=0;
                if(col0==0){entrada[0]=4;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col1==0){entrada[0]=5;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col2==0){entrada[0]=6;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col3==0){entrada[0]="B";}
                fila1=1;
                fila2=0;
                if(col0==0){entrada[0]=7;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col1==0){entrada[0]=8;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col2==0){entrada[0]=9;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col3==0){entrada[0]="C";if(num2_char!=NULL){contin2=4;resultado(num1_char,num2_char);}}//RESULTADO
                fila2=1;
                fila3=0;
                if(col0==0){entrada[0]="*";strcat(num2_char,entrada);}
                if(col1==0){entrada[0]=0;strcat(num2_char,entrada); contin2++;convertirnum2(num2_char);}
                if(col2==0){entrada[0]="#";}
                if(col3==0){entrada[0]="D";}
                fila3=1;
                __delay_ms(100);
            }
        }//else para cambio de numero
        
        //imprimir valores
        if(res_int==0){
            if(contin1<=3){
            //imprime el primer numero
                sprintf(buffer1,"Num1: %10d",num1_int);
                Lcd_Out2(1,1,buffer1);   
               // __delay_ms(500);
            }else{
            //imprime el segundo numero
                sprintf(buffer1,"Num2: %10d",num2_int);
                Lcd_Out2(1,1,buffer1);
               // __delay_ms(500);
            }
        }else{
            //imprime el resultado
                sprintf(buffer1,"RESULTADO= %10d",res_int);
                Lcd_Out2(1,1,buffer1);
               // __delay_ms(5000);
                res_int=0;
                contin1=1;
                contin2=1;
                num1_int=0;
                num2_int=0;
               // __delay_ms(500);
        }
    }//fin ciclo infinito
    return (EXIT_SUCCESS);
}

