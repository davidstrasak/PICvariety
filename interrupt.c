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

        TMR1 = 0xFFFF - (25000 - 1);    //Hazi interrupt 10x za sekundu
        TMR1IF = 0;                     //Vynulovani flagu
    }
    
    if(TMR1IE && TMR1IF && GAMEIE){
        GAMEtime += 1;
        
        TMR1 = 0xFFFF - (62500 - 1);    //Hazi interrupt 4x za sekundu
        TMR1IF = 0;                     //Vynulovani flagu
    }
    
    if(RC1IE && RC1IF && UARTIE){
        char temp = RCREG1;
        static int i = 0;
                
        if(temp != '\n'){
            gmail.data[i] = temp;
            i++;
        } else {
            gmail.full = 1;
            gmail.data[i] = '\0';
            i = 0;
        }
    }
    
    
}   