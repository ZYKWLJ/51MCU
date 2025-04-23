#include "experiment3.h"
#include "delay.h"
#include <REGX52.h>
//从00:00:00->23:59:59计时器
unsigned char hours=0;//时钟
unsigned char minutes=0;//分钟
unsigned char seconds=0;//秒钟
unsigned char count=0;//统计到达1s的1000次

void num2str(unsigned char *ptr, unsigned char num) {
    *(ptr) = (num/10) + '0';    // 十位
    *(ptr+1) = (num%10) + '0';  // 个位
}
unsigned char* time(unsigned char hours,unsigned char minutes,unsigned char seconds){
	//00:00:00共8位
	static unsigned char now[9];
	now[2]=now[5]=':';
	num2str(now+0,hours);
	num2str(now+3,minutes);
	num2str(now+6,seconds);
	now[8] = '\0';  // 添加字符串结束符
	return now;
}

void Timer0_Isr3(void) interrupt 1{
	//重置计数器TH、TL
	TL0 = 0x18;   // 设置定时初始值
    TH0 = 0xFC;   // 设置定时初始值
	count++;
	if(count==1000){
		 // 调试：翻转P2.0引脚观察中断是否触发
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
