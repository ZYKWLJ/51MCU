#ifndef _UART_H_
#define _UART_H_
#include<REGX52.h>
void Uart1_Init(void);
void Uart1_Isr(void);
void UART_SendByte(unsigned char Byte);
#endif
