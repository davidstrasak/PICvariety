
#include "includes.h"

void runUART(void){
    //GPIO
    TRISAbits.RA2 = 1;
    
    ANSELCbits.ANSC6 = 0;
    ANSELCbits.ANSC7 = 0;
    TRISCbits.TRISC6 = 1;   // TX pin jako vstup
    TRISCbits.TRISC7 = 1;   // rx pin jako vstup
   
    /*baudrate*/
    SPBRG1 = 25;              // (32_000_000 / (64 * 19200)) - 1
    
    TXSTA1bits.SYNC = 0;      // nastaveni asynchroniho modu
    RCSTA1bits.SPEN = 1;      // zapnuti UART
    TXSTA1bits.TXEN = 1;      // zapnuti TX
    RCSTA1bits.CREN = 1;      // zapnuti RX 
    
    UARTIE = 1;
    RC1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    uint8_t keepState = 1;
    
    while(keepState){        
        if(gmail.full){
            char reversed[31];
            int len = strlen(gmail.data);

            for(int i = 0; i < len; i++) {
                reversed[i] = gmail.data[len - 1 - i];
            }
            reversed[len] = '\0';
            printf("%s \n", reversed);
            
            gmail.full = 0;
            
            for(int p = 0; p < 31; p++) {
                gmail.data[p] = '\0';
            }
            
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