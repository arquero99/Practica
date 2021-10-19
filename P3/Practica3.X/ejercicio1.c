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
void getAnalog(void);
void dumpData(void);
void __interrupt() CAD_int(void);
void interrupt t0int (void);

int numInterruptT0=0;

void __interrupt() CAD_int(void){
    dumpData();
    PIR1bits.ADIF=0;    //Flag de interrupción CAD a 0
    //getAnalog();    //Llamada recursiva que actuará como bucle infinito
}

void interrupt t0int (void) //Interrupcion que saca el contenido por puertoB cada 500ns
{
    TMR0 =157;
    numInterruptT0++;
    if(numInterruptT0>=99){
        dumpData();
        numInterruptT0 = 0;
    }
    INTCONbits.T0IF=0; //Resetea la interrupción
}

void init_CAD(){
    //Configuración de puerto de entrada
    TRISAbits.TRISA0=1;    //Puerto A como entrada. Consultar a Norberto
    ANSELbits.ANS0=1;       //Establece entrada analogica. Idem
    //Puerto B de salida
    TRISBbits.TRISB0=0;
    //Configuración ADCON1
    ADCON1bits.ADFM=1;     //Justificado a la derecha.
    ADCON1bits.VCFG1=0;     //Ground como Vref-
    ADCON1bits.VCFG0=1;     //Vdd como Vref+
    //Configuración ADCON0
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

void getAnalog(void){
for(int i=0;i++;i<5){
            __nop(); //Para respetar el tiempo de carga del condensador insertamos 5 operaciones vacías
        }
for(int i=0;i++;i<88){
            __nop(); //Para respetar el tiempo de adquisicion X11 insertamos 88 operaciones vacías
        }
        //AQUI REALIZAMOS CONVERSION
ADCON0bits.GO=1;
}

void dumpData(void){
//Pasamos a Puerto B la salida de converosr A/D. Lo suyo es hacer PORTB[7]=ADRESH[0], PORB[6]=ADRESL[7] .....
PORTBbits.RB0=ADRESL.1;
PORTBbits.RB1=ADRESL.2;
PORTBbits.RB2=ADRESL.3;
PORTBbits.RB3=ADRESL.4;
PORTBbits.RB4=ADRESL.5;
PORTBbits.RB5=ADRESL.6;
}


int main() {
    PIE1bits.ADIE=1;    //Interrupcion CAD habilitada
    INTCONbits.PEIE=1;  //Interrupcion de periféricos habilitada        PREGUNTAR!!!!!!!!!!!!!!!!!
    INTCONbits.GIE=1;   //Interrupciones habilitadas
    init_CAD(); //Configuracion de puertos y encendido del CAD
    init_t0();
    while(1){
    getAnalog();
    //while(ADCON0bits.GO){}  //Espera mientras la conversion está en curso (Metodo sin usar interrupciones)
    while(!PIR1bits.ADIF) {}  //Esperamos hasta que llegue interrupción de conversor A/D
    while(!INTCONbits.T0IF){}                       //Espera de 500ms
    }
    return (EXIT_SUCCESS);
}

