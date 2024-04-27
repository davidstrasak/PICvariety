/*
 * File:   GPIO.c
 * Author: David
 *
 * Created on 28. dubna 2024, 0:32
 */

#include "includes.h"

    void LED1_Control(unsigned char state) { LED1 = state; }
    void LED2_Control(unsigned char state) { LED2 = state; }
    void LED3_Control(unsigned char state) { LED3 = state; }
    void LED4_Control(unsigned char state) { LED4 = state; }
    void LED5_Control(unsigned char state) { LED5 = state; }
    void LED6_Control(unsigned char state) { LED6 = state; }

//    void LEDSnake() {
//    unsigned char states[] = {0b100000, 0b110000, 0b011000, 0b001100, 0b000110, 0b000011, 0b000001, 0b000011, 0b000110, 0b001100, 0b011000, 0b110000};
//    int numStates = sizeof(states) / sizeof(states[0]);
//
//    for(int i = 0; i < numStates; i++) {
//        // For each state, turn on or off each LED as needed
//        for(int j = 0; j < 4; j++) {
//            (*LEDControl[j])((states[i] >> (3 - j)) & 0x1);
//        }
//        __delay_ms(500); // Delay for visibility, adjust as needed
//    }
//}

    
void runGPIO(void){
    //Init of LEDs
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
    
    //Init of buttons
    TRISAbits.RA2 = 1;
    ANSELAbits.ANSA2 = 0;
    
    //Other inits
    uint8_t keepState;
    keepState = 1;
    uint8_t GPIOindex;
    GPIOindex = 0;
    uint8_t GPIOreverse;
    GPIOreverse = 0;
    
    void (*LEDControl[])(unsigned char) = {LED1_Control, LED2_Control, LED3_Control, LED4_Control, LED5_Control, LED6_Control};
    
    while(keepState){
        
    unsigned char states[] = {0b100000, 0b110000, 0b011000, 0b001100, 0b000110, 0b000011, 0b000001, 0b000011, 0b000110, 0b001100, 0b011000, 0b110000};
    int numStates = sizeof(states) / sizeof(states[0]);

    for(int i = 0; i < numStates; i++) {
        // For each state, turn on or off each LED as needed
        for(int j = 0; j < 6; j++) {
            (*LEDControl[j])(!((states[i] >> (5 - j)) & 0x1));
        }
        __delay_ms(500); // Delay for visibility, adjust as needed
    }
        
        if(PORTAbits.RA2){
            __delay_ms(50);
            if(PORTAbits.RA2){
                while(PORTAbits.RA2);
                keepState = 0;
            }
        }
    }
    
    //Turn off the LEDs again
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED6 = 1;
    return;
}

