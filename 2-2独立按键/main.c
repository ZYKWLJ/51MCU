#include<REGX52.h>
void delay1ms(unsigned nms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(nms)
	{
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
		nms--;
	}
}

void test1(){//按下K1亮，松开灭
	while(1)
    {
        if(P3_1==0)
        {
            P2_0=0;
        }
        else
        {
            P2_0=1;
        }
    }
}

void test2(){//按下K1亮，再次按下灭，如此反复
	P2_0=1;
	while(1)
    {
        if(P3_1==0)
        {
			delay1ms(20);//消除按下的抖动
			while(P3_1==0);
			delay1ms(20);//消除松开的抖动
			P2_0=~P2_0;
        }
		
    }
	
}

void test3(){//每按下一次递增一个二进制位
// 2^8=256次
	unsigned int count=0;
	while(1){
		if(P3_1==0){
			delay1ms(20);
			while(P3_1==0);
			delay1ms(20);
			count++;
			P2=0xFF;//先统一置灭，再统一亮对应位！
			P2&=~count;
		}
	}
}

void test4(){//每隔10ms就递增二进制位
// 2^8=256次
	unsigned int count=0;
	while(1){
		while(P3_1==0);//按下暂停
		delay1ms(50);
		count++;
		P2=0xFF;//先统一置灭，再统一亮对应位！
		P2&=~count;
	}
}

void test5(){
	unsigned int initial=0x01;//每按下一次实现移位操作
	P2=~initial;
	while(1){
		if(P3_1==0){
			delay1ms(20);
			while(P3_1==0);
			delay1ms(20);
			initial<<=1;
			initial=initial>0x80?0x01:initial;
			P2=0xFF;
			P2=~initial;
		}
	}
}

void test6(){
	//移位操作自动化
unsigned int initial=0x01;
P2=~initial;
	while(1){
		delay1ms(100);
		initial<<=1;
		initial=initial>0x80?0x01:initial;
		P2=0xFF;
		P2=~initial;
	}
}

void main()
{
	test6();
}