/* 
 * File:   ejercicio1.c
 * Author: Juan Arquero
 *
 * Created on 4 de octubre de 2021, 13:28
 */
#include <xc.h>
#include <stdlib.h>

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF

void init_CAD();
void init_t0();
void __interrupt() t0int (void);

int numInterruptT0=0;
int puedoSeguir=0;


void __interrupt() t0int (void) //Interrupcion que saca el contenido por puertoB cada 500ns
{
    if(INTCONbits.T0IF){
         TMR0 =157;
         numInterruptT0++;
         if(numInterruptT0>=99){
           //GGO
            ADCON0bits.GO=1;
            numInterruptT0 = 0;
            
        }
        INTCONbits.T0IF=0; //Resetea la interrupci�n
    }
    else if (PIR1bits.ADIF){
        puedoSeguir=1;
        PIR1bits.ADIF=0;    //Flag de interrupci�n CAD a 0
    }
}

void init_CAD(){
    //Configuraci�n de puerto de entrada
    TRISA=1;    //Puerto A como entrada. Consultar a Norberto
    ANSEL=1;       //Establece entrada analogica. Idem
    //Puerto B de salida
    TRISB=0;
    //Configuraci�n ADCON1
    ADCON1bits.ADFM=1;     //Justificado a la derecha.
    ADCON1bits.VCFG1=0;     //Ground como Vref-
    ADCON1bits.VCFG0=1;     //Vdd como Vref+
    //Configuraci�n ADCON0
    ADCON0bits.ADCS=0b10;   //Para configurar reloj a Fosc/32 (20Mhz, 1.6uS) PAGINA 10 ESPECIFICO
    ADCON0bits.CHS=0b0000;  //Selecciona entrada AN0
    ADCON0bits.ADON=1;      //Enciende conversor
}

void init_t0()
{
    OPTION_REGbits.PS=0b111;
    OPTION_REGbits.T0CS=0;
    OPTION_REGbits.PSA=0;
    INTCONbits.T0IE=1;
}



int main() {
    PIE1bits.ADIE=1;    //Interrupcion CAD habilitada
    INTCONbits.PEIE=1;  //Interrupcion de perif�ricos habilitada        PREGUNTAR!!!!!!!!!!!!!!!!!
    INTCONbits.GIE=1;   //Interrupciones habilitadas
    init_CAD(); //Configuracion de puertos y encendido del CAD
    init_t0();
    while(1){
    
        //while(!PIR1bits.ADIF) {}  //Esperamos hasta que llegue interrupci�n de conversor A/D
    
        //while(!INTCONbits.T0IF){}                       //Espera de 500ms
    
        while(puedoSeguir){
             PORTB=ADRESL;
             puedoSeguir=0;
        }
    }
    
    return (EXIT_SUCCESS);
}

//        PORTB=ADRESL;                    //Volcado en puertoB dentro de interrupcion
