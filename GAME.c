/*
 * File:   GAME.c
 * Author: David
 *
 * Created on 17. kvetna 2024, 14:05
 */

#include "includes.h"

void runGAME(void){
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
    
    //ADC init
    ANSELAbits.ANSA5 = 1;

    ADCON2bits.ADFM = 1;            //right justified
    ADCON2bits.ADCS = 0b110;        //Fosc/64
    ADCON2bits.ACQT = 0b110;        //16 TAD
    ADCON0bits.ADON = 1;            //ADC zapnout

    //Promenne init
    uint16_t pot1;                  // promenna pro vysledek prevodu
    char text[17] = "";             // retezec zatim prazdny
    uint8_t keepState = 1;

    while(keepState){
        //Cteni prvniho potaku
        ADCON0bits.CHS = 5;                         // kanal AN5
        GODONE = 1;                                 // spustit aproximaci
        while(GODONE);                              // cekam nez je hotovo
        pot1 = (uint16_t)((ADRESH << 8) | ADRESL);  // cteni vysledku

        sprintf(text, "%hu             ", pot1);
        LCD_ShowString(2, text);

        if(PORTAbits.RA2){  //Kontrola drzeni pinu s debouncingem
            __delay_ms(50);
            if(PORTAbits.RA2){
                while(PORTAbits.RA2);
                keepState = 0;
            }
        }
    }

    // Uklizeni
    ADCON0bits.ADON = 0;

    return;
}