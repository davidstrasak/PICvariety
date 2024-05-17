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
    uint8_t keepStateGAME;
    
    //Init of the timer
    //Timer 1
    T1CONbits.TMR1CS = 0b00;    //Clock delenej 4 (FOSC/4)
    T1CONbits.T1CKPS = 0b11;    //Prescaler 1:8
    TMR1IE = 1;                 //TMR1 Interrupt enable
    PEIE = 1;
    GIE = 1;
    GAMEIE = 1;
    TMR1IF = 1;
    TMR1 = 0xFFFF - (62500 - 1);    //Hazi interrupt 4x za sekundu
    TMR1ON = 1;                 //Tenhle bit je tak dulezitej, ze ma vlastni definovane makro
    //Other inits
    GAMEtime = 0;
    uint8_t GAMEround = 1;
    uint8_t GAMEpart = 0;
    uint8_t GAMEdivider = 0;
    char approxText[25] = "";
    
    //Actual game initialisation
    uint16_t randomNumber;
    randomNumber = (uint16_t)(2 + rand() / (RAND_MAX / (1023 - 2 + 1) + 1));
    sprintf(approxText, "%u                ", randomNumber);
    LCD_ShowString((char)1, approxText);
    keepStateGAME = 1;
    

    while(keepStateGAME){
        //Cteni prvniho potaku
        ADCON0bits.CHS = 4;                         // kanal AN4
        GODONE = 1;                                 // spustit aproximaci
        while(GODONE);                              // cekam nez je hotovo
        pot1 = (uint16_t)((ADRESH << 8) | ADRESL);  // cteni vysledku

        sprintf(text, "%hu             ", pot1);
        LCD_ShowString((char)2, text);
        
        switch(GAMEround){
            case 1:
                GAMEdivider = 26;
                break;
            case 2:
                GAMEdivider = 24;
                break;
            case 3:
                GAMEdivider = 18;
                break;
            case 4:
                GAMEdivider = 16;
                break;
            default:
                GAMEdivider = 15;
                break;
        }
        
        GAMEpart = GAMEtime/GAMEdivider;
        switch(GAMEpart){
            case 0:
                LED1 = 1;
                LED2 = 1;
                LED3 = 1;
                LED4 = 1;
                LED5 = 1;
                LED6 = 1;
                break;
            case 1:
                LED1 = 0;
                LED2 = 1;
                LED3 = 1;
                LED4 = 1;
                LED5 = 1;
                LED6 = 1;
                break;
            case 2:
                LED1 = 0;
                LED2 = 0;
                LED3 = 1;
                LED4 = 1;
                LED5 = 1;
                LED6 = 1;
                break;
            case 3:
                LED1 = 0;
                LED2 = 0;
                LED3 = 0;
                LED4 = 1;
                LED5 = 1;
                LED6 = 1;
                break;
            case 4:
                LED1 = 0;
                LED2 = 0;
                LED3 = 0;
                LED4 = 0;
                LED5 = 1;
                LED6 = 1;
                break;
            case 5:
                LED1 = 0;
                LED2 = 0;
                LED3 = 0;
                LED4 = 0;
                LED5 = 0;
                LED6 = 1;
                break;
            case 6:
                LED1 = 0;
                LED2 = 0;
                LED3 = 0;
                LED4 = 0;
                LED5 = 0;
                LED6 = 0;
                break;
            case 7:
                GAMEtime = 0;
                if(pot1 >= randomNumber - 2 && pot1 <= randomNumber + 2){ // Cislo musi byt v intervalu do 1 od randomNumber (me se to ladi blbe)
                    GAMEround += 1;
                    randomNumber = (uint16_t)(2 + rand() / (RAND_MAX / (1023 - 2 + 1) + 1));
                    sprintf(approxText, "%u                ", randomNumber);
                    keepStateGAME = 1;      //sprintf mi z nejakyho duvodu meni tuhle promennou, takze si ji musim znovu definovat. Asi pretekl.
                    LCD_ShowString((char)1, approxText);
                } else {
                    ADCON0bits.ADON = 0;
                    sprintf(approxText, "Skore: %u        ", GAMEround - 1);
                    LCD_ShowString((char)1, "GAME OVER       ");
                    LCD_ShowString((char)2, approxText);
                    keepStateGAME = 0;
                    __delay_ms(2000);
                }
                break;
        }
        
        if(PORTAbits.RA2){  //Kontrola drzeni pinu s debouncingem
            __delay_ms(50);
            if(PORTAbits.RA2){
                while(PORTAbits.RA2);
                keepStateGAME = 0;
            }
        }
    }

    // Uklizeni
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    LED5 = 1;
    LED6 = 1;
    TMR1ON = 0; //Vypnuti timeru aby nedelal bordel v menu a dalsich modulech
    TMR1IE = 0;
    GAMEIE = 0; //Vypni interrupt pro GAME funkci

    return;
}