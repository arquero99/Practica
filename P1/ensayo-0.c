#include <xc.h>

// See /opt/microchip/xc8/v<version>/docs/chips/16f886.html
// for details on #pragma config

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF


void main(void)
{ char x;

  OSCCON = 0b00001000; // External cristal

  x = 0;
  ANSEL = 0;	// Configure as digital all CAD channels
  ANSELH = 0;
  TRISA = 0; 	// Configure port A as output
  TRISB = 0;

  while(1) //Bucle infinito
  { PORTB = x;
    x += 1;
   } 
}
