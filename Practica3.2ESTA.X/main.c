/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 25 de septiembre de 2018, 23:48
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

#define col0 PORTBbits.RB5  //COlumna original en RA0
#define col1 PORTAbits.RA1
#define col2 PORTAbits.RA2
#define col3 PORTAbits.RA3

int cont1=3;
int cont2=3;
int numero1=0;
int numero2=0;
int resultado=0;
int operacion=0;//1 suma  2 resta
int o=0;
float d=0;
float d2=0;
int igual=0;
int aux=0;
void n1(int valor, int contador){
    if(contador==3){numero1=numero1+valor;}
    if(contador==2){numero1=numero1*10+valor;}
    if(contador==1){numero1=numero1*10+valor;}
}
void n2(int valor, int contador){
    if(contador==3){numero2=numero2+valor;}
    if(contador==2){numero2=numero2*10+valor;}
    if(contador==1){numero2=numero2*10+valor;}
}
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    PORTA=0;
    TRISA=0b00001111;
    WPUA=0b11111111;
    WPUBbits.WPUB5=1;
    ANSELBbits.ANSB5=0;
    TRISBbits.TRISB5=1;
    ANSELA=0;
    PORTD=0;
    PORTC=0;
    ANSELD=0;
    ANSELC=0;
    unsigned char buffer1[16];
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    
    while(1){
        while(operacion==0){
        //Nnumero 1
        while(cont1>0){
            
            fila0=1;fila1=1;fila2=1;fila3=1;
            fila0=0;
            __delay_ms(1);
            if(col0==0){n1(1,cont1);cont1--;}//manda el #1
            if(col1==0){n1(2,cont1);cont1--;}//manda el #2
            if(col2==0){n1(3,cont1);cont1--;}//manda el #3
            if(col3==0){cont1=0;operacion=1;}//operacion=1 SUMA  //manda A
            fila0=1;
            fila1=0;
            __delay_ms(1);
            if(col0==0){n1(4,cont1);cont1--;}//manda el #4
            if(col1==0){n1(5,cont1);cont1--;}//manda el #5
            if(col2==0){n1(6,cont1);cont1--;}//manda el #6
            if(col3==0){cont1=0;operacion=2;}//operacion=0 RESTA //manda B
            fila1=1;
            fila2=0;
            __delay_ms(1);
            if(col0==0){n1(7,cont1);cont1--;}//manda el #7
            if(col1==0){n1(8,cont1);cont1--;}//manda el #8
            if(col2==0){n1(9,cont1);cont1--;}//manda el #9
            if(col3==0){return (EXIT_SUCCESS);}                    //manda   C
            fila2=1;
            fila3=0;
            __delay_ms(1);
            if(col0==0){cont1=0;operacion=4;}//manda * Multiplicacion
            if(col1==0){n1(0,cont1);cont1--;}//manda el #0
            if(col2==0){}//manda el #
            if(col3==0){cont1=0;operacion=3;}//manda D DIVISION
            fila3=1;
            sprintf(buffer1," Num1= %03d",numero1);
            Lcd_Out2(1,1,buffer1);
            __delay_ms(250);
        }
        //esperar por operacion
         fila0=1;fila1=1;fila2=1;fila3=1;
            fila0=0;
            __delay_ms(1);
            if(col0==0){}//manda el #1
            if(col1==0){}//manda el #2
            if(col2==0){}//manda el #3
            if(col3==0){cont1=0;operacion=1;}//operacion=1 SUMA  //manda A
            fila0=1;
            fila1=0;
            __delay_ms(1);
            if(col0==0){}//manda el #4
            if(col1==0){}//manda el #5
            if(col2==0){}//manda el #6
            if(col3==0){cont1=0;operacion=2;}//operacion=0 RESTA //manda B
            fila1=1;
            fila2=0;
            __delay_ms(1);
            if(col0==0){}//manda el #7
            if(col1==0){}//manda el #8
            if(col2==0){}//manda el #9
            if(col3==0){return (EXIT_SUCCESS);}                    //manda   C
            fila2=1;
            fila3=0;
            __delay_ms(1);
            if(col0==0){cont1=0;operacion=4;}//manda * Multiplicacion
            if(col1==0){}//manda el #0
            if(col2==0){}//manda el #
            if(col3==0){cont1=0;operacion=3;}//manda D DIVISION
            fila3=1;
            sprintf(buffer1," Num1= %03d",numero1);
            Lcd_Out2(1,1,buffer1);
            __delay_ms(250);
        }
        /*if(operacion==1){
        Lcd_Out(1,1,"SUMA");
            __delay_ms(500);
        }else if(operacion==2){
            Lcd_Out(1,1,"RESTA");
            __delay_ms(500);
        
        }*/
        //fin numero 1
        
         //numero 2
        while(igual==0){
        while(cont2>0){
            fila0=1;fila1=1;fila2=1;fila3=1;
            fila0=0;
            __delay_ms(1);
            if(col0==0){n2(1,cont2);cont2--;}//manda el #1
            if(col1==0){n2(2,cont2);cont2--;}//manda el #2
            if(col2==0){n2(3,cont2);cont2--;}//manda el #3
            if(col3==0){}//operacion=1 SUMA  //manda A
            fila0=1;
            fila1=0;
            __delay_ms(1);
            if(col0==0){n2(4,cont2);cont2--;}//manda el #4
            if(col1==0){n2(5,cont2);cont2--;}//manda el #5
            if(col2==0){n2(6,cont2);cont2--;}//manda el #6
            if(col3==0){}//operacion=0 RESTA //manda B
            fila1=1;
            fila2=0;
            __delay_ms(1);
            if(col0==0){n2(7,cont2);cont2--;}//manda el #7
            if(col1==0){n2(8,cont2);cont2--;}//manda el #8
            if(col2==0){n2(9,cont2);cont2--;}//manda el #9
            if(col3==0){return (EXIT_SUCCESS);}                    //manda   C
            fila2=1;
            fila3=0;
            __delay_ms(1);
            if(col0==0){}//manda *
            if(col1==0){n2(0,cont2);cont2--;}//manda el #0
            if(col2==0){cont2=0; igual=1;}//manda el # DA EL RESULTADO
            if(col3==0){}//manda D
            fila3=1;
            __delay_ms(1);
            sprintf(buffer1," Num2= %03d",numero2);
            Lcd_Out2(1,1,buffer1);
            __delay_ms(250);
        }//fin numero 2
        //esperar por igual
        //esperar por operacion
         fila0=1;fila1=1;fila2=1;fila3=1;
            fila0=0;
            __delay_ms(1);
            if(col0==0){}//manda el #1
            if(col1==0){}//manda el #2
            if(col2==0){}//manda el #3
            if(col3==0){}//operacion=1 SUMA  //manda A
            fila0=1;
            fila1=0;
            __delay_ms(1);
            if(col0==0){}//manda el #4
            if(col1==0){}//manda el #5
            if(col2==0){}//manda el #6
            if(col3==0){}//operacion=0 RESTA //manda B
            fila1=1;
            fila2=0;
            __delay_ms(1);
            if(col0==0){}//manda el #7
            if(col1==0){}//manda el #8
            if(col2==0){}//manda el #9
            if(col3==0){return (EXIT_SUCCESS);}                    //manda   C
            fila2=1;
            fila3=0;
            __delay_ms(1);
            if(col0==0){}//manda *
            if(col1==0){}//manda el #0
            if(col2==0){cont2=0;igual=1;}//manda el # igual
            if(col3==0){}//manda D
            fila3=1;
            sprintf(buffer1," Num2= %03d",numero2);
            Lcd_Out2(1,1,buffer1);
            __delay_ms(250);
        
        }
        if(operacion==1){
            
            if(aux==0){Lcd_Cmd(LCD_CLEAR); aux=1;}
            
            o=numero1+numero2;
        sprintf(buffer1," Res= %03d",o);
        Lcd_Out2(1,1,buffer1);
        ////////////////////////////////////////////////////
        //esperar por clear
        fila0=1;fila1=1;fila2=1;fila3=1;
            
            fila2=0;
            __delay_ms(1);
            if(col3==0){return (EXIT_SUCCESS);}                    //manda   C
            fila2=1;
            
        /////////////////////////////////////////////////////////////
            
        }else if(operacion==2){
            
            if(aux==0){Lcd_Cmd(LCD_CLEAR); aux=1;}
            
            o=numero1-numero2;
            sprintf(buffer1," Res= %03d",o);
            Lcd_Out2(1,1,buffer1);
            ////////////////////////////////////////////////////
        //esperar por clear
        fila0=1;fila1=1;fila2=1;fila3=1;
            fila2=0;
            __delay_ms(1);
            if(col3==0){return (EXIT_SUCCESS);}                    //manda   C
            fila2=1;
            
        /////////////////////////////////////////////////////////////
        }else if(operacion==3){
            if(aux==0){Lcd_Cmd(LCD_CLEAR); aux=1;}
            
            d=(float)numero1;
            d2=(float)numero2;
            sprintf(buffer1," Res= %06f",(d/d2));
        Lcd_Out2(1,1,buffer1);
            ////////////////////////////////////////////////////
        //esperar por clear
        fila0=1;fila1=1;fila2=1;fila3=1;
            fila2=0;
            __delay_ms(1);
            if(col3==0){return (EXIT_SUCCESS);}                    //manda   C
            fila2=1;
        }else if(operacion==4){
            if(aux==0){Lcd_Cmd(LCD_CLEAR); aux=1;}
            
            o=numero1*numero2;
            sprintf(buffer1," Res= %06d",o);
            Lcd_Out2(1,1,buffer1);
            ////////////////////////////////////////////////////
            //esperar por clear
            fila0=1;fila1=1;fila2=1;fila3=1;
            fila2=0;
            __delay_ms(1);
            if(col3==0){return (EXIT_SUCCESS);}                    //manda   C
            fila2=1;
        }//fin de elses de operaciong       
        
        
}//fin del ciclo infinito
    
    
    return (EXIT_SUCCESS);
    }


