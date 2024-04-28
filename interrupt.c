/*
 * File:   interrupt.c
 * Author: David
 *
 * Created on 28. dubna 2024, 15:14
 */


#include "includes.h"

void __interrupt() ISR(void){   
    if(TMR1IE && TMR1IF && GPIOIE){

        if(PORTAbits.RA2){  //Kontrola drzeni pinu s debouncingem
            __delay_ms(50);
            if(PORTAbits.RA2){
                while(PORTAbits.RA2);
                keepStateGPIO = 0;
            }
        }

        TMR1 = 0xFFFF - (25000 - 1);    //Hazi interrupt kazdych 40x za sekundu
        TMR1IF = 0;                     //Vynulovani flagu
    }
}   