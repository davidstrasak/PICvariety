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
#define _XTAL_FREQ 32E6
void putch(char data);
#endif