/*
 * File:   DAC.c
 * Author: David
 *
 * Created on 27. dubna 2024, 21:57
 */
#include "includes.h"


void runDAC(void) {
    //GPIO
    TRISCbits.RC0 = 1;
    TRISAbits.RA4 = 1;
    TRISAbits.RA3 = 1;
    TRISAbits.RA2 = 1;
    ANSELAbits.ANSA3 = 0;
    ANSELAbits.ANSA2 = 0;
    
    //SPI setup
    TRISBbits.RB3 = 0;  // Slave select
    TRISCbits.RC3 = 0;  // Serial clock - je vystup protoze MCU je master
    TRISCbits.RC5 = 0;  // Serial data out
    
    SSP1CON1bits.SSPM = 0b0010;     //Master FOSC / 64
    SSP1CON1bits.CKP = 0;
    SSP1STATbits.CKE = 1;
    SSP1CON1bits.SSPEN = 1;
    
    /* nastaveni ADC*/
    ANSELBbits.ANSB0 = 1;
//    ANSELBbits.ANSB5 = 1;
    ADCON2bits.ADFM = 0;            //Left justified
    ADCON2bits.ADCS = 0b110;        //Fosc/64
    ADCON2bits.ACQT = 0b110;        //16
    ADCON0bits.ADON = 1;            //ADC zapnout

    /*baudrate*/
    SPBRG1 = 25;                // (32_000_000 / (64 * 19200)) - 1
    RCSTA1bits.SPEN = 1;        // zapnuti UART
    TXSTA1bits.SYNC = 0;        // nastaveni asynchroniho modu
    TXSTA1bits.TXEN = 1;        // zapnuti TX
    RCSTA1bits.CREN = 1;        // zapnuti RX 
    
    //Chip select
    LATBbits.LB3 = 1;
    
    ADCON0bits.CHS = 12;
    
    uint8_t selectModeDAC = 1;
    uint8_t keepState;
    keepState = 1;
    uint8_t DACindex = 0;
    
    while(keepState){
        switch(selectModeDAC){
            case 1: // Trojuhelnik
                if(DACindex<255/2){
                    SPI_write((uint8_t)(1.9*DACindex));
                }
                if(DACindex>=255/2){
                    SPI_write((uint8_t)(1.9*(255-DACindex)));
                }
                break;
            case 2: // Sinus
                SPI_write((uint8_t)(255/2*sin(2*3.14*DACindex/255)+255/2));
                break;
            case 3: // Pila
                SPI_write(255 - DACindex);
                break;
        }
        GODONE = 1;
        while(GODONE);

        printf("%d \r", ADRESH);
        if(PORTCbits.RC0){
            selectModeDAC = 1;
        }
        if(PORTAbits.RA4){
            selectModeDAC = 2;
        }
        if(PORTAbits.RA3){
            selectModeDAC = 3;
        }
        if(PORTAbits.RA2){
            keepState = 0;
        }
        DACindex++;
        __delay_ms(10);
        }
    return;
}

void SPI_write (uint8_t data){
    uint8_t MSB, LSB;
    
    MSB = (uint8_t)(0b00110000 | (data >> 4));
    LSB = (uint8_t)(data << 4);
    
    LATBbits.LB3 = 0;
    
    SSP1BUF = MSB; 
    while(!SSP1IF);
    SSP1IF = 0;
    
    SSP1BUF = LSB;
    while(!SSP1IF);
    SSP1IF = 0;
    
    LATBbits.LB3 = 1;
}