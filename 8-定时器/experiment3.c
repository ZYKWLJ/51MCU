#include "experiment3.h"
#include "delay.h"
#include <REGX52.h>
//��00:00:00->23:59:59��ʱ��
unsigned char hours=0;//ʱ��
unsigned char minutes=0;//����
unsigned char seconds=0;//����
unsigned char count=0;//ͳ�Ƶ���1s��1000��

void num2str(unsigned char *ptr, unsigned char num) {
    *(ptr) = (num/10) + '0';    // ʮλ
    *(ptr+1) = (num%10) + '0';  // ��λ
}
unsigned char* time(unsigned char hours,unsigned char minutes,unsigned char seconds){
	//00:00:00��8λ
	static unsigned char now[9];
	now[2]=now[5]=':';
	num2str(now+0,hours);
	num2str(now+3,minutes);
	num2str(now+6,seconds);
	now[8] = '\0';  // ����ַ���������
	return now;
}

void Timer0_Isr3(void) interrupt 1{
	//���ü�����TH��TL
	TL0 = 0x18;   // ���ö�ʱ��ʼֵ
    TH0 = 0xFC;   // ���ö�ʱ��ʼֵ
	count++;
	if(count==1000){
		 // ���ԣ���תP2.0���Ź۲��ж��Ƿ񴥷�
		P2_0 = ~P2_0;
		count=0;
		seconds++;
		minutes+=seconds/60;
		hours+=minutes/60;
		minutes%=60;
		seconds%=60;
		lcd1602_show_string(0,0,time(hours,minutes,seconds));
	}
}
