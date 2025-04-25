#include <REGX52.h>
#include "lcd1602.h"
#include "uart.h"
void main()
{
    unsigned char Sec = 0;
    Uart1_Init();
    lcd1602_init();
    while (1)
    {
        char str[2];
        UART_SendByte(Sec++);
        str[0] = Sec + '0';
        str[1] = '\0';
        lcd1602_show_string(0, 0, str);
        delay_ms(1000);
    }
}
