#include <stdio.h> //libreria de entradas y salidas estandar
#include <stdlib.h>
#include "config.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"
/*
 * 
 */
int main(int argc, char** argv) {
    OSCFRQbits.HFFRQ=0b110;
    ANSELC=0b00000000;
    ANSELD=0b00000000;
    //TRIS PARA DEFINIR SI ES ENTRADA O SALIDA
    //ANSEL PARA DEFINIR SI ES ANALOGICO O DIGITAL
    //PORT PARA DEFINIR SI ES LECTURA
    //LAT PARA DEFINIR SI ES ESCRITURA
    unsigned char buffer1[16],buffer2[16];
    int i=0,cont=0;
    
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
     
      Lcd_Cmd(LCD_BLINK_CURSOR_ON);
    __delay_ms(1000);
    Lcd_Cmd(LCD_CURSOR_OFF);
    
    
        for(int i2=0;i2<16;i2++){
           // __delay_ms(10);
        /*
         printf(buffer2,"  MECATRONICA   ");   
        Lcd_Out2(1,i2,buffer2);
        __delay_ms(10);
         */
        if(i2==0){
        //Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"  MECATRONICA!  ");
        __delay_ms(10);
        }else if(i2==1){ 
            //Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"   MECATRONICA! ");
        __delay_ms(10);
        }else if(i2==2){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"    MECATRONICA!");
        __delay_ms(10);
        }else if(i2==3){
            //Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"!    MECATRONICA");
        __delay_ms(10);
        }else if(i2==4){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"A!    MECATRONIC");
        __delay_ms(10);
        }else if(i2==5){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"CA!    MECATRONI");
        __delay_ms(10);
        }else if(i2==6){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"ICA!    MECATRON");
        __delay_ms(10);
        }else if(i2==7){
            //Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"NICA!    MECATRO");
        __delay_ms(10);
        }else if(i2==8){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"ONICA!    MECATR");
        __delay_ms(10);
        }else if(i2==9){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"RONICA!    MECAT");
        __delay_ms(10);
        }else if(i2==10){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"TRONICA!    MECA");
        __delay_ms(10);
        }else if(i2==11){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"ATRONICA!    MEC");
        __delay_ms(10);
        }else if(i2==12){
           // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"CATRONICA!    ME");
        __delay_ms(10);
        }else if(i2==13){
            //Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"ECATRONICA!    M");
        __delay_ms(10);
        }else if(i2==14){
          // Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0,"MECATRONICA!    ");
        __delay_ms(10);
        }else if(i2==15){
            //Lcd_Cmd(LCD_CLEAR);
        Lcd_Out(1,0," MECATRONICA!   ");
        __delay_ms(10);
        }
        sprintf(buffer1," Contador= %02d",cont);
        Lcd_Out2(2,1,buffer1);
        if(cont==12){
            cont=0;
        }else{
            cont=cont+1;
        }
        if(i2==15){
            i2=0;
        }
        __delay_ms(500);
        }
        
           
   //while(1);
    
    return (EXIT_SUCCESS);
}

