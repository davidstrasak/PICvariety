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
    uint8_t setUpAgain = 0;
    
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
                switch(menuI){
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        LCD_ShowString((char)1, "RB0-A2, BR: 9600");
                        LCD_ShowString((char)2, "1:tr,2:sin,3:pil");
                        runDAC();
                        setUpAgain = 1;
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                }
            }
            
        }
        if(PORTAbits.RA2){
            
        }
        
        if(setUpAgain){
        menuI = moveDisplay(menuI,0);
        setUpAgain = 0;
        }
    }
    return;
}