#include "uart.h"
#include "lcd1602.h"

void UART_Routine() interrupt 4//串口接受自电脑的数据处理中断函数
{
	if (RI)				//检测串口1接收中断
	{
		P2=~SBUF;				//读取数据，取反后输出到LED
		UART_SendByte(SBUF);	//将受到的数据发回串口
		RI = 0;			//清除串口1接收中断请求位
	}
}


void UART_SendByte(unsigned char Byte){//串口像电脑发送
	SBUF=Byte;
	while(TI==0){//等待发送成功
		
	}
	TI=0;//重置发送成功的位

}
void Uart1_Init(void)	//4800bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}
