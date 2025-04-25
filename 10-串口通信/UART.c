#include "uart.h"

void Uart1_Isr(void) interrupt 4
{
	if (TI)				//��⴮��1�����ж�
	{
		TI = 0;			//�������1�����ж�����λ
	}
	if (RI)				//��⴮��1�����ж�
	{
		RI = 0;			//�������1�����ж�����λ
	}
}

void UART_SendByte(unsigned char Byte){
	SBUF=Byte;
	while(TI==0){//�ȴ����ͳɹ�
		
	}
	TI=0;//���÷��ͳɹ���λ

}
void Uart1_Init(void)	//4800bps@11.0592MHz
{
	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xF4;			//���ö�ʱ��ʼֵ
	TH1 = 0xF4;			//���ö�ʱ����ֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
	ES = 1;				//ʹ�ܴ���1�ж�
}
