#include <REGX52.h>
void timer_init_0()
{
    TMOD = 0x01;          // 工作在模式1，0000 0001
    TF0 = 0;              // 中断标志位初始值为0
    TR0 = 1;              // 定时器0开始运行
    TH0 = 64536 >> 8;     // 中断计时高8位赋初值，相当于64535/256
    TL0 = 64536 & 0x00FF; // 中断计时低8位赋初值，相当于64535%256
    ET0 = 1;              // 允许定时器0中断
    EA = 1;               // 允许总中断
    PT0 = 0;              // 低优先级
}

void main()
{
    timer_init_0();
    while (1)
    {
    }
}

void Timer0_Routine(void) interrupt 1//这是定时器0的中断函数,内置的，我们按着实现就好！
{
    unsigned int T0Count;
    // 达到了1ms，重新计时下一个1ms
    TH0 = 64536 >> 8;     // 中断计时高8位赋初值，相当于64535/256
    TL0 = 64536 & 0x00FF; // 中断计时低8位赋初值，相当于64535%256
    T0Count++;
    if (T0Count == 1000)
    {
        T0Count = 0;
        P2_0 = ~P2_0;
    }
}