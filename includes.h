#ifndef INCLUDES
#define	INCLUDES
#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "lcd.h"
#include "configs.h"
#include "DAC.h"
#include "menu.h"
#include "GPIO.h"
#include "interrupt.h"
#include "ADC.h"
#include "PWM.h"
#include "UART.h"
#include "GAME.h"
#include "MUSIC.h"
#define _XTAL_FREQ 32E6
void putch(char data);
#define LED1 LATDbits.LD2
#define LED2 LATDbits.LD3
#define LED3 LATCbits.LC4
#define LED4 LATDbits.LD4
#define LED5 LATDbits.LD5
#define LED6 LATDbits.LD6
#endif