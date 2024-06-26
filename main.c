/*
 * File:   main.c
 * Author: student
 *
 * Created on 22 April 2024, 14:16
 */

#include "includes.h"

void main(void) {
    __delay_ms(100);
    // Menu GPIO
    TRISCbits.RC0 = 1;
    TRISAbits.RA4 = 1;
    TRISAbits.RA3 = 1;
    TRISAbits.RA2 = 1;
    ANSELAbits.ANSA3 = 0;
    ANSELAbits.ANSA2 = 0;
    
    //Vypnuti LEDek aby porad nesvitily
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
    
    // Dalsi inicializace
    LCD_Init();
    uint8_t menuI = 0;          //menuI je promenna co si predava index menu pokazde co ho zmenim
    uint8_t setUpAgain = 0;
    
    LCD_ShowString((char)1, "Vytvoril:       ");
    LCD_ShowString((char)2, "David Strasak   ");
    __delay_ms(2000);
    
    //Zobrazeni menu
    menuI = moveDisplay(menuI,0);
    
    while(1){
        if(PORTCbits.RC0){ //btn1
            __delay_ms(50);
            if(PORTCbits.RC0){
                menuI = moveDisplay(menuI,2);
                while(PORTCbits.RC0);
            }
        }
        if(PORTAbits.RA4){ //btn2
            __delay_ms(50);
            if(PORTAbits.RA4){
                menuI = moveDisplay(menuI,1);
                while(PORTAbits.RA4);
            }
        }
        if(PORTAbits.RA3){ //btn3
            __delay_ms(50);
            if(PORTAbits.RA3){
                while(PORTAbits.RA3);
                switch(menuI){
                    case 0: // GPIO
                        LCD_ShowString((char)1, "Pozor! Had!!!   ");
                        LCD_ShowString((char)2, "                ");
                        runGPIO();
                        setUpAgain = 1;
                        break;
                    case 1: // UART
                        LCD_ShowString((char)1, "BR: 19200       ");
                        LCD_ShowString((char)2, "Konec - new line");
                        runUART();
                        setUpAgain = 1;
                        break;
                    case 2: // PWM
                        LCD_ShowString((char)1, "Zmacknete BTN2  ");
                        LCD_ShowString((char)2, "                ");
                        runPWM();
                        setUpAgain = 1;
                        break;
                    case 3: // ADC
                        LCD_ShowString((char)1, "Volty na POTech:");
                        runADC();
                        setUpAgain = 1;
                        break;
                    case 4: // DAC
                        LCD_ShowString((char)1, "RB0-A2, BR:19200");
                        LCD_ShowString((char)2, "1:tr,2:sin,3:pil");
                        runDAC();
                        setUpAgain = 1;
                        break;
                    case 5: // GAME
                        LCD_ShowString((char)1, "Ladeni potaku   ");
                        LCD_ShowString((char)2, "                ");
                        __delay_ms(1000);
                        LCD_ShowString((char)1, "Hybej pomoci    ");
                        LCD_ShowString((char)2, "POT1            ");
                        __delay_ms(2000);
                        LCD_ShowString((char)1, "Zrychli to      ");
                        LCD_ShowString((char)2, "pomoci BTN4     ");
                        __delay_ms(2000);
                        LCD_ShowString((char)1, "Pripravit       ");
                        LCD_ShowString((char)2, "                ");
                        __delay_ms(1000);
                        LCD_ShowString((char)2, "           Pozor");
                        __delay_ms(2000);
                        runGAME();
                        setUpAgain = 1;
                        break;
                    case 6: // MUSIC
                        LCD_ShowString((char)1, "Nebylo          ");
                        LCD_ShowString((char)2, "Implementovano  ");
                        __delay_ms(2000);
                        runMUSIC();
                        setUpAgain = 1;
                        break;
                }
            }
            
        }
        if(PORTAbits.RA2){ //btn4
            
        }
        
        if(setUpAgain){
        menuI = moveDisplay(menuI,0);
        setUpAgain = 0;
        }
    }
    return;
}