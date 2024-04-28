#ifndef INTERRUPT
#define INTERRUPT
//GPIO
uint8_t keepStateGPIO;  //Musi byt globalni promena aby se mohla dostat do interruptu
uint8_t GPIOIE;         //GPIO interrupt enable (neni definovan MCU. Definoval jsem si ho sam)
#endif