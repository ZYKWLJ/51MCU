#include <REGX52.h>
void Timer0_Isr(void) interrupt 1
{
    unsigned int T0Count;
    TL0 = 0x18; // 设置定时初始值
    TH0 = 0xFC; // 设置定时初始值
    T0Count++;
    if (T0Count == 100)
    {
        T0Count = 0;
        P2_0 = ~P2_0;
    }
}

void Timer0_Init(void) // 1毫秒@12.000MHz
{
    // AUXR &= 0x7F;			//定时器时钟12T模式
    TMOD &= 0xF0; // 设置定时器模式
    TMOD |= 0x01; // 设置定时器模式
    TL0 = 0x18;   // 设置定时初始值
    TH0 = 0xFC;   // 设置定时初始值
    TF0 = 0;      // 清除TF0标志
    TR0 = 1;      // 定时器0开始计时
    ET0 = 1;      // 使能定时器0中断
    EA = 1;       // 使能总中断
}

void main()
{
    Timer0_Init();
    while (1)
    {
    }
}
