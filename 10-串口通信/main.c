#include <REGX52.h>
#include "lcd1602.h"
#include "uart.h"
void MCU2Computer(){ 
	static unsigned char Sec;
	char str[2];
	UART_SendByte(Sec++);
	str[0] = Sec + '0';
	str[1] = '\0';
	lcd1602_show_string(0, 0, str);
	delay_ms(1000);
}
void main()
{
   
    Uart1_Init();//´®¿Ú³õÊ¼»¯
    lcd1602_init();
    while (1)
    {
		MCU2Computer();
    }
}
