/*
 * File:   main.c
 * Author: student
 *
 * Created on 22 April 2024, 14:16
 */

#include "includes.h"

void main(void) {
    // Menu GPIO
    TRISCbits.RC0 = 1;
    TRISAbits.RA4 = 1;
    TRISAbits.RA3 = 1;
    TRISAbits.RA2 = 1;
    ANSELAbits.ANSA3 = 0;
    ANSELAbits.ANSA2 = 0;
    
    // Other initialising
    LCD_Init();
    uint8_t menuI = 0;
    
    // Menu setup
    moveDisplay(menuI,0);
    
    while(1){
        if(PORTCbits.RC0){
            __delay_ms(50);
            if(PORTCbits.RC0){
                while(PORTCbits.RC0);
                menuI = moveDisplay(menuI,2);
            }
        }
        if(PORTAbits.RA4){
            __delay_ms(50);
            if(PORTAbits.RA4){
                while(PORTAbits.RA4);
                menuI = moveDisplay(menuI,1);
            }
        }
        if(PORTAbits.RA3){
            __delay_ms(50);
            if(PORTAbits.RA3){
                while(PORTAbits.RA3);
                
            }
            
        }
        if(PORTAbits.RA2){
            
        }
    }
    return;
}