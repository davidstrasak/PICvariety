/*
 * File:   menu.c
 * Author: David
 *
 * Created on 28. dubna 2024, 0:06
 */


#include "includes.h"

uint8_t moveDisplay(uint8_t menuI, uint8_t where){
    LCD_Clear();
    char* menuItems[] = {"GPIO", "UART", "PWM", "ADC", "DAC", "GAME", "MUSIC", ""};
    switch (where){
        case 0://init
            break;
        case 1://forwards
            if(menuI<6){
            menuI++;
            }
            break;
        case 2://backwards
            if(menuI>0){
            menuI--;
            }
            break;
    }
    char menuItem1[17];
    char menuItem2[17];
    sprintf(menuItem1, ">%-*s", 15, menuItems[menuI]);
    sprintf(menuItem2, "%-*s", 16, menuItems[menuI+1]);  
    LCD_ShowString((char)1, menuItem1);
    LCD_ShowString((char)2, menuItem2);
    
    return menuI;
}
