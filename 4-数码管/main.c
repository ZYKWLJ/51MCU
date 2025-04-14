#include<REGX52.h>
void delay(unsigned nms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(nms)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		nms--;
	}
}

unsigned int arr[11]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00/*全灭*//*0110,1111*/};//0~9的段码

// 依次对应 8 个数码管的选择
// 这里将 P2_2、P2_3、P2_4 的状态反映在一个字节的第 2、3、4 位
// 根据正确的位选逻辑修改 P2_arr 数组
unsigned char P2_arr[8] = {
    0x1C,  // 0001 1100: LSC=1, LSB=1, LSA=1 → 数码管 0
    0x18,  // 0001 1000: LSC=1, LSB=1, LSA=0 → 数码管 1
    0x14,  // 0001 0100: LSC=1, LSB=0, LSA=1 → 数码管 2
    0x10,  // 0001 0000: LSC=1, LSB=0, LSA=0 → 数码管 3
    0x0C,  // 0000 1100: LSC=0, LSB=1, LSA=1 → 数码管 4
    0x08,  // 0000 1000: LSC=0, LSB=1, LSA=0 → 数码管 5
    0x04,  // 0000 0100: LSC=0, LSB=0, LSA=1 → 数码管 6
    0x00   // 0000 0000: LSC=0, LSB=0, LSA=0 → 数码管 7
};


void test1(){
	P2 = P2_arr[0];
	P0 = 0x06; // 显示数字1（b和c段亮,因为单片机自动上电IO口为阳极，所以需要手动将0个口赋值为0还是1，否则全亮影响结果）（或者P0=arr[2]）
}


unsigned int count=0;
void test2(){
	P2 = P2_arr[0];
	P0=0x00;
	while(1){
		P0=arr[count++%10];
		delay(1000);
	}	
}

unsigned int count1=0;

void test3(){//驱动第一到八个管子(动态显示)。
	P0=0x00;
	while(1){
		int i=0;
		for(;i<8;i++){
			delay(1);
			P2=P2_arr[i];
			P0=arr[i];
		}
	}
}


int total_0=99999999;
int total_1=99999999;
int num(int index){//返回指定位的数字，注意本身的位数判断！去掉前导0	
	int ret=total_1;
	int i=0;//统计位数
    int retArr[8] = {10, 10, 10, 10, 10, 10, 10, 10}; // 默认全灭
	for(;ret>0;i++){//统计可能的每一位
		retArr[i]=ret%10;
		ret/=10;
	}
	if(index>i)return 10;//超出位数的统一不亮
	return retArr[index-1];
}

unsigned int delayInternal=1;//每一个数码管的延时显示

void test4(){//驱动第一到八个管子, 倒计时99999999秒。
	P0=0x00;//初始状态全为0，即灭
	while(1){
		unsigned int count=0;
		P2=0X00;
		//8个管子会维持1s
		while(count<1000){
			int i = 1;
			for (; i <= 8; i++) { // 动态扫描显示八个数码管
				P2=P2_arr[i-1];//选中哪一个数码管
				P0 = arr[num(i)];//选中当前数码管的那几个段，即打印当前数码管
				delay(delayInternal); // 短暂延时，用于显示
				P0 = 0x00; // 消隐
				count+=delayInternal;
			}
		}
		total_1--;
		if(total_1==0)total_1=total_0;//循环
	}
}


void test5(){//驱动第一到八个管子, 倒计时99999999秒。
	P0=0x00;//初始状态全为0，即灭
	while(1){
		unsigned int count=0;
		P2=0X00;
		//8个管子会维持1s
		while(count<1000){
			int i = 1;
			for (; i <= 8; i++) { // 动态扫描显示八个数码管
				P2=P2_arr[7-(i-1)];//选中哪一个数码管(从右减小)
				P0 = arr[num(i)];//选中当前数码管的那几个段，即打印当前数码管
				delay(delayInternal); // 短暂延时，用于显示
				P0 = 0x00; // 消隐
				count+=delayInternal;
			}
		}
		total_1--;
		if(total_1==0)total_1=total_0;//循环
	}
}

void main()
{
	test5();
	while(1);
}