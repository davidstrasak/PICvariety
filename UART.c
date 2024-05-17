/*
 * File:   UART.c
 * Author: student
 *
 * Created on 29 April 2024, 15:02
 */


#include "includes.h"

void runUART(void){
    //GPIO
    TRISAbits.RA2 = 1;
    
    ANSELC = 0x00;          // vypnuti analogovych funkci na PORTC
    TRISD = 0x00;           // PORTD jako vystup
    TRISCbits.TRISC6 = 1;   // TX pin jako vstup
    TRISCbits.TRISC7 = 1;   // rx pin jako vstup
   
    /*baudrate*/
    SPBRG1 = 25;              // (32_000_000 / (64 * 19200)) - 1
    
    TXSTA1bits.SYNC = 0;      // nastaveni asynchroniho modu
    RCSTA1bits.SPEN = 1;      // zapnuti UART
    TXSTA1bits.TXEN = 1;      // zapnuti TX
    RCSTA1bits.CREN = 1;      // zapnuti RX 
    
    RC1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    uint8_t keepState = 1;
    
    while(keepState){        
        if(gmail.full){
            LED1 ^= 1;
            printf("Dostal jsem %s \n",gmail.data);
            gmail.full = 0;
        }
        
        if(PORTAbits.RA2){
            __delay_ms(50);
            if(PORTAbits.RA2){
                while(PORTAbits.RA2);
                keepState = 0;
            }
        }
        
    }
    
    //Uklizeni 
    RCSTA1bits.SPEN = 0;
    TXSTA1bits.TXEN = 0;
    RCSTA1bits.CREN = 0;
    UARTIE = 0;
    RC1IE = 0;
    PEIE = 0;
    GIE = 0;
    return;
}