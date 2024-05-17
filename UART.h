#ifndef UART
#define UART
void runUART(void);
typedef struct{
    char data[10];
    char full;
} mailbox;
volatile mailbox gmail = {0,0,0};
#endif