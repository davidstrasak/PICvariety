#ifndef INTERRUPT
#define INTERRUPT
//GPIO
uint8_t keepStateGPIO;  //Musi byt globalni promena aby se mohla dostat do interruptu
uint8_t GPIOIE;         //GPIO interrupt enable (neni definovan MCU. Definoval jsem si ho sam)
uint8_t UARTIE;         //UART interrupt enable
uint8_t GAMEIE;         //GAME interrupt enable
uint8_t GAMEtime;       //Musi byt globalni promenna, pocita se aby posouvala LEDky ve hre
#endif