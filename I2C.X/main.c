/* 
 * File:   main.c
 * Author: drasf
 *
 * Created on 8 de noviembre de 2018, 13:35
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"
//LCD<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
 SSPSTAT register 
 SMP CKE D/A P S R/W UA BF
 
 BF:
 1=Cuando la transmision ahun esta progreso
 0=transmision de datos completa
 
 S
 se genero senal de star
 
 P
 Se genero una senal de stop
  
 R/W
 Maestro
 1=transmision en progreso
 0=transmicion ya no esta en progreso, para checar el estado del ack
 Esclavo
 
 
 SSPxCON1 register para configuracion
 WCOL SSPOV SSPEN CKP SSPM3 SSPM2 SSPM1 SSPM0
 Los primeros (SSPM3-SSPM0) 4 bits para seleccionar el modo checar en datasheet
 el modo usado sera: 
 >>>>>>>>>>>>>1000 I2C modo maestro clock=fosc/(4SSPADD+1)
 SSPEN 
 1=habilita los pines SCL Y SDA como fuente de la comuniacacion
 
 SSPxCON2 register
 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>NOTA para mandar un mensaje a todos los dispositivos conecatdos a la red el ultimo bit de la direccion sera 0
 0=GCEN ACKSTAT ACKDT ACKEN RCEN PEN RSEN SEN
 * GCEN Habilita interrupcion ciandp existe una llamdad general
 * ACKSTAT 
 * 1=No se recibio una ack
 * 0=se recibio un ack
 * ACKDT
 * 1=Se trasmite el noack al iniciar una secuacnia de ack
 * 0=se transmite un ack al iniciar la secuencia de ack
 * ACKEN
 * 1=Inicia secuencia de ack
 * 0=Secuancia de ack sin usar
 * RCEN
 * 1=habilita recepcion en modo I2C
 * 0=Recepcion sin usar
 * PEN
 * 1=manda la signal de stop
 * 0=condicion de stop sin usar
 * RSEN
 * 1=inicia condicion de restar
 * 0=condicion de restar sin usar
 * 
 * SSPxADD
 * modo esclavo
 * 
 * modo maestro sirve para seleccionar o generar la signal de reloj
 * >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>PAGINA DEL DATA 494
 * <>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>PARA SELECCIONAR LA FRECUENCIA HAY QUE CHECAR EL DATASHEET DEL RELOJ
 * 
 */
int main(int argc, char** argv) {
    int x,y;
    
    OSCFRQbits.HFFRQ=0b110;//32MHz
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>configuracion de pines C como digitales
    ANSELC=0;
    //LOS PINES SDA Y SDL ENTRADAS DIGITALES <<<<<<<<<<<<<<<<<<<<<<<<<<<< POR PPS
    SSP1CLKPPS=0x13;// PAGINA 237 y 236
    SSP1DATPPS=0x14;
    
    //I2C CONFIGURATIONS
    SSP1CON1bits.SSPEN=1;
    SSP1CON1bits.SSPM=0b1000;
    SSP1ADD=0x13;
    //TRAMA DE ESCRITURA PARA CONFIGURACION INICIAL 
    SSP1CON2bits.SEN=1; //GENERA SIGNAL DE STAR
    while(SSP1CON2bits.SEN);//ESPERA A QUE el bit sea 
    SSP1BUF=0b11010000;//DIRECCION RTC+bit de escritura
    while(SSP1STATbits.BF);//espera hasta que sea;
    while(SSP1STATbits.R_nW);//esperael 9no ciclo
    //****************************************************verificar si llego un ack o un no ack 
    //SIN EL ESCLAVO CONTESTO NACK SSP1CON2bits.ACKSTAT
    SSP1BUF=0x00;//comienza a escribir en el registro 0x00 
    while(SSP1STATbits.BF);//ESPERA HASTA QUE 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo 
    SSP1BUF=0x00;//CH=0 INICIAR ,SEG=00
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo 
    SSP1BUF=0b00000101;//MIN=05
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1BUF=0b00010101;//HR=15
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1BUF=0b00000010;//LUNES
    while(SSP1STATbits.BF);//ESPERA HASTA QUE SE VACEE EL BUFFER 
    while(SSP1STATbits.R_nW);//ESPERA EL 9no ciclo
    SSP1CON2bits.PEN=1;//generamos un signal de stop
    while(SSP1CON2bits.PEN);
    /*
     MODO LECTURA
     * MANDAR SEFUNDA DIRECION COON EL BIT DE ESCRITURA 
     * EL ESCLAVO TIENE QUE MANDAR EUN ACK
     * Y CAMBIAR EL MODO DE RECEPCION DEL MASTER
     * ESPERAR HASA QUE LLEGUE EL DATO
     * LEER BUIFFER DE ENTRADA
     * ACKDT=1 MANDA NO ACK PARA DETENER LA TRAMA
     * ACKEN=1 GENERA EL NOAK
     * ESPERAR A QUE SE MANDE EL NOACK
     * PEN=1;
     * WHILE(PEN);
     * USAR VARIABLE LEIDA
     * 
     * //metodo para pasar al fomato del registro
     * x=35/10
     * y=var-
    */
    Lcd_Init();     //inicializamos el lcd
    Lcd_Cmd(LCD_CLEAR);		//limpiamos lcd
    Lcd_Cmd(LCD_CURSOR_OFF);	//apagamos el cursor
    /*
     sprintf(buffer1,"   %d:%d:%d",hora1,min1,seg1);
     Lcd_Out2(1, 1, buffer1);
     */
    while(1){
    
    }
            return (EXIT_SUCCESS);
}

