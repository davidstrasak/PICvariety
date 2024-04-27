/*
 * File:   main.c
 * Author: student
 *
 * Created on 22 April 2024, 14:16
 */

#include "includes.h"


void SPI_write (uint8_t data);
void putch(char data);

void main(void) {
    
    //GPIO
    TRISCbits.RC0 = 1;
    TRISAbits.RA4 = 1;
    TRISAbits.RA3 = 1;
    ANSELAbits.ANSA3 = 0;
    
    //SPI setup
    TRISBbits.RB3 = 0;  // Slave select
    TRISCbits.RC3 = 0;  // Serial clock - is an output because the controller is acting as a master
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
    SPBRG1 = 51;                // (32_000_000 / (64 * 9600)) - 1
    RCSTA1bits.SPEN = 1;        // zapnuti UART
    TXSTA1bits.SYNC = 0;        // nastaveni asynchroniho modu
    TXSTA1bits.TXEN = 1;        // zapnuti TX
    RCSTA1bits.CREN = 1;        // zapnuti RX 
    
    //Chip select
    LATBbits.LB3 = 1;
    
    ADCON0bits.CHS = 12;
    
    uint8_t selectMode = 1;
    
    while(1){
        for(uint8_t i = 0; 1; i++){
        switch(selectMode){
            case 1:
                if(i<255/2){
                    SPI_write(1.9*i);
                }
                if(i>=255/2){
                    SPI_write(1.9*(255-i));
                }
                break;
            case 2:
                SPI_write((255/2*sin(2*3.14*i/255)+255/2));
                break;
            case 3:
                SPI_write(255 - i);
                break;
        }
        GODONE = 1;
        while(GODONE);

        printf("%d \r", ADRESH);
        if(PORTCbits.RC0){
            selectMode = 1;
        }
        if(PORTAbits.RA4){
            selectMode = 2;
        }
        if(PORTAbits.RA3){
            selectMode = 3;
        }
        
        __delay_ms(10);
        }
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

void putch(char data){
    while(!TX1IF);
    TXREG1 = data;
}