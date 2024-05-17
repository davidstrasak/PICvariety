/*
 * File:   ADC.c
 * Author: David
 *
 * Created on 28. dubna 2024, 17:12
 */


#include "includes.h"



void runADC(void){
    
//ADC init
ANSELAbits.ANSA5 = 1;
ANSELEbits.ANSE0 = 1;

ADCON2bits.ADFM = 1;            //right justified
ADCON2bits.ADCS = 0b110;        //Fosc/64
ADCON2bits.ACQT = 0b110;        //16 TAD
ADCON0bits.ADON = 1;            //ADC zapnout

//Promenne init
uint16_t pot1, pot2;            // promenna pro vysledek prevodu
float voltage1, voltage2;       // promenna pro hodnotu ve voltech
char text[17] = "";             // retezec zatim prazdny
uint8_t keepState = 1;

while(keepState){
    //Cteni prvniho potaku
    ADCON0bits.CHS = 5;                         // kanal AN5
    GODONE = 1;                                 // spustit aproximaci
    while(GODONE);                              // cekam nez je hotovo
    pot1 = (uint16_t)((ADRESH << 8) | ADRESL);  // cteni vysledku
    voltage1 = (float)pot1 / (float)(1023) * (float)(3.3);         // konverze ADC do voltu

    //Cteni druheho potaku
    ADCON0bits.CHS = 4;                         // kanal AN4
    GODONE = 1;                                 // spustit aproximaci
    while(GODONE);                              // cekam nez je hotovo
    pot2 = (uint16_t)((ADRESH << 8) | ADRESL);  // cteni vysledku
    voltage2 = (float)pot2 / (float)(1023) * (float)(3.3);         // konverze ADC do voltu

    sprintf(text, "POT1:%.1fPOT2:%.1f", voltage1, voltage2);
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
