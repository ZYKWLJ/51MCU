#include "experiment1.h"
static unsigned int T0Count=0;
void Timer0_Isr1(void) interrupt 1
{
    
    TL0 = 0x18; // 设置定时初始值
    TH0 = 0xFC; // 设置定时初始值
    T0Count++;
    if (T0Count == 100)
    {
        T0Count = 0;
        P2_0 = ~P2_0;
    }
}
