#ifndef UART
#define UART
void runUART(void);
typedef struct{
    char data[60];
    char full;
} mailbox;
volatile mailbox gmail = {"", 0};
#endif