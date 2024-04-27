/*
 * File:   main.c
 * Author: student
 *
 * Created on 22 April 2024, 14:16
 */

#include "includes.h"

uint8_t menuI = 0;

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
    char* menuItems[] = {"GPIO", "UART", "PWM", "ADC", "DAC", "GAME", "MUSIC", ""};
    char menuItem1[17];
    char menuItem2[17];
    
    // Menu setup
    LCD_Reset;
    sprintf(menuItem1, "%-*s", 16, menuItems[menuI]);
    sprintf(menuItem2, "%-*s", 16, menuItems[menuI+1]);  
    LCD_ShowString((char)1, menuItem1);
    LCD_ShowString((char)2, menuItem2);
    
    while(1){
        
    }
    return;
}
