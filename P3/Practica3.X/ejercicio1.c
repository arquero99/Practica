/* 
 * File:   ejercicio1.c
 * Author: alumno
 *
 * Created on 4 de octubre de 2021, 13:28
 */
#include <xc.h>
#include <stdlib.h>

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF


/*
 * 
 */

void init_CAD(){
    //Configuración de puerto
    TRISAbits.TRISA0=1;    //Puerto A como entrada. Consultar a Norberto
    ANSELbits.ANS0=1;       //Establece entrada analogica. Idem
    //Configuración ADCON1
    ADCON1bits.ADFM=1;     //Justificado a la derecha.
    ADCON1bits.VCFG1=0;     //Ground como Vref-
    ADCON1bits.VCFG0=1;     //Vdd como Vref+
    //Configuración ADCON0
    ADCON0bits.ADCS=0b10;   //Para configurar reloj a Fosc/32 (20Mhz, 1.6uS)
    ADCON0bits.CHS=0b0000;  //Selecciona entrada AN0
    ADCON0bits.ADON=1;      //Enciende conversor
}
void __interrupt() CAD_int(void){
    getAnalog();    //Llamada recursiva que actuará como bucle infinito
    PIR1bits.ADIF=0;    //Flag de interrupción CAD a 0
}

void getAnalog(void){
for(int i=0;i++;i<18){
            __nop(); //Para respetar el tiempo de adquisicionX2 insertamos 16 operaciones vacías
        }
        //AQUI REALIZAMOS CONVERSION
ADCON0bits.GO=1;
}


int main() {
    PIE1bits.ADIE=1;    //Interrupcion CAD habilitada
    INTCONbits.PEIE=1;  //Interrupcion de periféricos habilitada
    INTCONbits.GIE=1;   //Interrupciones habilitadas
    
    return (EXIT_SUCCESS);
}

