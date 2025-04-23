#include "experiment2.h"
#include "delay.h"

volatile unsigned char keyNum = 0;
volatile unsigned char P2_init = 0x01;
unsigned char key(){
    if(P3_1 == 0){  // ��ⰴ������
        delay_ms(20);  // ����
        if(P3_1 == 0){  // ȷ�ϰ���
            while(P3_1 == 0);  // �ȴ��ͷ�
            delay_ms(20);  // �ͷ�����
            keyNum = !keyNum;  // �л�״̬
        }
    }
    return keyNum;
}

static unsigned int T0Count = 0;

void Timer0_Isr2(void) interrupt 1
{
    TL0 = 0x18;
    TH0 = 0xFC;
    T0Count++;
    if (T0Count == 500)
    {
        T0Count = 0;
        if(keyNum){ // �����ƶ�
            P2_init = (P2_init >> 1) | (P2_init << 7); // ѭ������
            P2 = ~P2_init;
        }else{ // �����ƶ�
            P2_init = (P2_init << 1) | (P2_init >> 7); // ѭ������
            P2 = ~P2_init;
        }
    }
}