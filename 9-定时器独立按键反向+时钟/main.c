#include <REGX52.h>
#include "lcd1602.h"
//��00:00:00->23:59:59��ʱ��
unsigned char hours=0;//ʱ��
unsigned char minutes=0;//����
unsigned char seconds=0;//����
unsigned char test=0;

void num2str(unsigned char *ptr, unsigned char num) {
    *(ptr) = (num/10) + '0';    // ʮλ
    *(ptr+1) = (num%10) + '0';  // ��λ
}

static unsigned char now[9];
unsigned char* time(unsigned char hours,unsigned char minutes,unsigned char seconds){
	//00:00:00��8λ	
	now[2]=now[5]=':';
	num2str(now+0,hours);
	num2str(now+3,minutes);
	num2str(now+6,seconds);
	now[8] = '\0';  // ����ַ���������
	return now;
}



void Timer0_Init(void) // 1����@12.000MHz
{
    // AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
    TMOD &= 0xF0; // ���ö�ʱ��ģʽ
    TMOD |= 0x01; // ���ö�ʱ��ģʽ
    TL0 = 0x18;   // ���ö�ʱ��ʼֵ
    TH0 = 0xFC;   // ���ö�ʱ��ʼֵ
    TF0 = 0;      // ���TF0��־
    TR0 = 1;      // ��ʱ��0��ʼ��ʱ
    ET0 = 1;      // ʹ�ܶ�ʱ��0�ж�
    EA = 1;       // ʹ�����ж�
}

void main()
{
	unsigned char prevSeconds = seconds; // ��¼��һ�ε�����
    Timer0_Init();
    lcd1602_init();
    lcd1602_show_string(0, 0, time(hours, minutes, seconds)); // ��ʼ��ʾ
    while (1) {
		char str[2];
		str[0]=test%10+'0';
		str[1]='\0';
		lcd1602_show_string(0, 1,str);
        if (seconds != prevSeconds) { // ֻ�������仯ʱ�Ÿ�����ʾ����ֹCPU���Ĺ���
            lcd1602_show_string(8, 1, time(hours, minutes, seconds));
            prevSeconds = seconds;
        }
    }
}
static unsigned int count=0;

void Timer0_ISR(void) interrupt 1
{
	//Ϊʲô������������countʹ�þͻᵼ����Զ���²��ˣ�����������Ҳ���У�����һ���ӣ�
	//������ִ�е� static unsigned int count; ��һ�д���ʱ��ȷ�е�˵�ǵ�һ�ν�������������ĺ���ʱ����count �����ᱻ�Զ���ʼ��Ϊ 0 ��
	//�жϺ���׼�򣬲�Ҫ��������ӹ�������
	//���ü�����TH��TL
	TL0 = 0x18;   // ���ö�ʱ��ʼֵ
    TH0 = 0xFC;   // ���ö�ʱ��ʼֵ
	count++;
	
	if(count == 1000) {
        P2_0 = ~P2_0;  // �����źţ������û������˵��������û�����жϣ�զ��ģ�
        count = 0;
        seconds++;
        test++;
        // ����ʱ������߼�
        if(seconds >= 60) {
            seconds = 0;
            minutes++;
            if(minutes >= 60) {
                minutes = 0;
                hours++;
                if(hours >= 24) {
                    hours = 0;
                }
            }
        }
        
    }
}