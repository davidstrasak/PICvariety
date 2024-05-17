/*
 * File:   PWM.c
 * Author: David
 *
 * Created on 28. dubna 2024, 19:56
 */


#include "includes.h"

void runPWM(void){
    // PWM init
    TRISCbits.RC2 = 1;              //Dam PWM CCP3 na input RB3 
    CCPTMRS0bits.C1TSEL = 0b00;     //Nastaveni timeru na tmr2
    PR2 = 199;                      //10 kHz
    CCP1CONbits.CCP1M |= 0b1100;    //Nastaveni jako PWM a nastaveni single output
    CCP1CONbits.P1M = 0b10;         //Half bridge
    CCPR1L = 0;                     //inicializace stridy
    TMR2IF = 0;
    TMR2ON = 1;
    while(!TMR2IF);                 //Cekan na konec timeru abych zacal na jeho zacatku
    TRISCbits.RC2 = 1;              //PWM porad jako input aby mi nejel motor kdyz to nechci
    
    // GPIO init
    TRISAbits.RA4 = 1;
    TRISAbits.RA2 = 1;
    // Vypnuti LEDek aby porad nesvitily
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISCbits.RC4 = 0;
    TRISDbits.RD4 = 0;
    TRISDbits.RD5 = 0;
    TRISDbits.RD6 = 0;
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED6 = 1;
    
    uint8_t keepState;
    keepState = 1;
    
    uint8_t multiplier;
    multiplier = 0;
    
    while(keepState){
        
        CCPR1L = multiplier*199/5;
        
        if(PORTAbits.RA4){
            __delay_ms(50);
            if(PORTAbits.RA4){
                while(PORTAbits.RA4);
                if(multiplier == 5 ){
                    multiplier = 0;
                } else if(multiplier <5){
                    multiplier++;
                }
            }
        }
        
        if(PORTAbits.RA2){  //Kontrola drzeni pinu s debouncingem
        __delay_ms(50);
        if(PORTAbits.RA2){
            while(PORTAbits.RA2);
            keepState = 0;
        }
    }
        

    }
    // Uklizeni nastaveni do menu
    CCP1CONbits.CCP1M = 0b0000;
    TMR2ON = 0;
    TMR2IE = 0;
    return;
}