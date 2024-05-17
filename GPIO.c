/*
 * File:   GPIO.c
 * Author: David
 *
 * Created on 28. dubna 2024, 0:32
 */

#include "includes.h"
//Funkce nastaveni LED aby bylo mozne z nich udelat matici kterym muzu cyklit
void LED1_Control(unsigned char state) { LED1 = state; }
void LED2_Control(unsigned char state) { LED2 = state; }
void LED3_Control(unsigned char state) { LED3 = state; }
void LED4_Control(unsigned char state) { LED4 = state; }
void LED5_Control(unsigned char state) { LED5 = state; }
void LED6_Control(unsigned char state) { LED6 = state; }

//V teto funkci jsou potreba globalni promenne definovane v interrupt.h a samotna interrupt funkce.

void runGPIO(void){
    //Init of LEDs
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISCbits.RC4 = 0;
    TRISDbits.RD4 = 0;
    TRISDbits.RD5 = 0;
    TRISDbits.RD6 = 0;
    ANSELDbits.ANSD2 = 0;
    ANSELDbits.ANSD3 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELDbits.ANSD4 = 0;
    ANSELDbits.ANSD5 = 0;
    ANSELDbits.ANSD6 = 0;
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED6 = 1;
    
    //Init of buttons
    TRISAbits.RA2 = 1;
    ANSELAbits.ANSA2 = 0;
    
    
    //Init of the timer
    //Timer 1
    T1CONbits.TMR1CS = 0b00;    //Clock delenej 4 (FOSC/4)
    T1CONbits.T1CKPS = 0b11;    //Prescaler 1:8
    TMR1IE = 1;                 //TMR1 Interrupt enable
    PEIE = 1;
    GIE = 1;
    GPIOIE = 1;
    TMR1IF = 1;
    TMR1 = 0xFFFF - (25000 - 1);    //Hazi interrupt kazdych 40x za sekundu
    TMR1ON = 1;                 //Tenhle bit je tak dulezitej, ze ma vlastni definovane makro
    
    //Other inits
    keepStateGPIO = 1;      //Je inicializovane globalne
    uint8_t GPIOindex;
    GPIOindex = 0;
    uint8_t GPIOreverse;
    GPIOreverse = 0;
    
    void (*LEDControl[])(unsigned char) = {LED1_Control, LED2_Control, LED3_Control, LED4_Control, LED5_Control, LED6_Control};
    unsigned char states[] = {0b100000, 0b110000, 0b011000, 0b001100, 0b000110, 0b000011, 0b000001, 0b000011, 0b000110, 0b001100, 0b011000, 0b110000};
    int numberOfStates = sizeof(states) / sizeof(states[0]);
    uint8_t GPIOi;  //Pocitaci index
    GPIOi = 0;
    
    while(keepStateGPIO){
        
        for(int j = 0; j < 6; j++) {    //Nastaveni hodnot kazde LED zvlast
            (*LEDControl[j])(!((states[GPIOi] >> (5 - j)) & 0x1));
        }
        __delay_ms(400);
        GPIOi++;
        if(GPIOi == numberOfStates){
            GPIOi = 0;
        }
    }
    
    // Uklizeni nastaveni do menu
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED6 = 1;
    TMR1ON = 0; //Vypnuti timeru aby nedelal bordel v menu a dalsich modulech
    TMR1IE = 0;
    GPIOIE = 0; //Vypni interrupt pro GPIO funkci
    return;
}

