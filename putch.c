/*
 * File:   putch.c
 * Author: David
 *
 * Created on 27. dubna 2024, 22:53
 */


#include "includes.h"

void putch(char data){
    while(!TX1IF);
    TXREG1 = data;
}