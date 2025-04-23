#include "experiment2.h"
#include "delay.h"

volatile unsigned char keyNum = 0;
volatile unsigned char P2_init = 0x01;
unsigned char key(){
    if(P3_1 == 0){  // 检测按键按下
        delay_ms(20);  // 消抖
        if(P3_1 == 0){  // 确认按下
            while(P3_1 == 0);  // 等待释放
            delay_ms(20);  // 释放消抖
            keyNum = !keyNum;  // 切换状态
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
        if(keyNum){ // 反向移动
            P2_init = (P2_init >> 1) | (P2_init << 7); // 循环右移
            P2 = ~P2_init;
        }else{ // 正向移动
            P2_init = (P2_init << 1) | (P2_init >> 7); // 循环左移
            P2 = ~P2_init;
        }
    }
}