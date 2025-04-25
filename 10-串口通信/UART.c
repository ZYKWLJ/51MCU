#include "uart.h"
#include "lcd1602.h"

void UART_Routine() interrupt 4//���ڽ����Ե��Ե����ݴ����жϺ���
{
	if (RI)				//��⴮��1�����ж�
	{
		P2=~SBUF;				//��ȡ���ݣ�ȡ���������LED
		UART_SendByte(SBUF);	//���ܵ������ݷ��ش���
		RI = 0;			//�������1�����ж�����λ
	}
}


void UART_SendByte(unsigned char Byte){//��������Է���
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
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	EA=1;
	ES=1;
}
