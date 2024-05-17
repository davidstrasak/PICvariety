#ifndef UART
#define UART
void runUART(void);
typedef struct{
    char data[31];
    char full;
} mailbox;
volatile mailbox gmail = {"", 0};
#endif