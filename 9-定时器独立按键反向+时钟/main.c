#include <REGX52.h>
#include "lcd1602.h"
//从00:00:00->23:59:59计时器
unsigned char hours=0;//时钟
unsigned char minutes=0;//分钟
unsigned char seconds=0;//秒钟
unsigned char test=0;

void num2str(unsigned char *ptr, unsigned char num) {
    *(ptr) = (num/10) + '0';    // 十位
    *(ptr+1) = (num%10) + '0';  // 个位
}

static unsigned char now[9];
unsigned char* time(unsigned char hours,unsigned char minutes,unsigned char seconds){
	//00:00:00共8位	
	now[2]=now[5]=':';
	num2str(now+0,hours);
	num2str(now+3,minutes);
	num2str(now+6,seconds);
	now[8] = '\0';  // 添加字符串结束符
	return now;
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
	unsigned char prevSeconds = seconds; // 记录上一次的秒数
    Timer0_Init();
    lcd1602_init();
    lcd1602_show_string(0, 0, time(hours, minutes, seconds)); // 初始显示
    while (1) {
		char str[2];
		str[0]=test%10+'0';
		str[1]='\0';
		lcd1602_show_string(0, 1,str);
        if (seconds != prevSeconds) { // 只有秒数变化时才更新显示，防止CPU消耗过重
            lcd1602_show_string(8, 1, time(hours, minutes, seconds));
            prevSeconds = seconds;
        }
    }
}
static unsigned int count=0;

void Timer0_ISR(void) interrupt 1
{
	//为什么不在这里声明count使用就会导致永远更新不了？包括在外面也不行？这是一个坑！
	//当程序执行到 static unsigned int count; 这一行代码时（确切地说是第一次进入包含该声明的函数时），count 变量会被自动初始化为 0 。
	//中断函数准则，不要在里面添加过长任务！
	//重置计数器TH、TL
	TL0 = 0x18;   // 设置定时初始值
    TH0 = 0xFC;   // 设置定时初始值
	count++;
	
	if(count == 1000) {
        P2_0 = ~P2_0;  // 调试信号，这里就没进来，说明根本就没触发中断！咋搞的！
        count = 0;
        seconds++;
        test++;
        // 修正时间计算逻辑
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