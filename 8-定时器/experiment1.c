#include "experiment1.h"

void Timer0_Isr1(void) interrupt 1
{
    static unsigned int T0Count;
    TL0 = 0x18; // ���ö�ʱ��ʼֵ
    TH0 = 0xFC; // ���ö�ʱ��ʼֵ
    T0Count++;
    if (T0Count == 100)
    {
        T0Count = 0;
        P2_0 = ~P2_0;
    }
}
