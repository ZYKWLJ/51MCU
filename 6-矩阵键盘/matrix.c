#include "matrix.h"

unsigned char matrixKey(){
	
	unsigned char KeyNumber=0;
	P1=0xFF;//ȫ��1
	P1_3=0;//ɨ���1��
	if(P1_7==0){delay_ms(10);while(P1_7==0);delay_ms(10);KeyNumber=1;}//ɨ���1��
	if(P1_6==0){delay_ms(10);while(P1_6==0);delay_ms(10);KeyNumber=5;}//ɨ���2��
	if(P1_5==0){delay_ms(10);while(P1_5==0);delay_ms(10);KeyNumber=9;}//ɨ���3��
	if(P1_4==0){delay_ms(10);while(P1_4==0);delay_ms(10);KeyNumber=13;}//ɨ���4��
	
	P1=0xFF;//ȫ��1
	P1_2=0;//ɨ���2��
	if(P1_7==0){delay_ms(10);while(P1_7==0);delay_ms(10);KeyNumber=2;}//ɨ���1��
	if(P1_6==0){delay_ms(10);while(P1_6==0);delay_ms(10);KeyNumber=6;}//ɨ���2��
	if(P1_5==0){delay_ms(10);while(P1_5==0);delay_ms(10);KeyNumber=10;}//ɨ���3��
	if(P1_4==0){delay_ms(10);while(P1_4==0);delay_ms(10);KeyNumber=14;}//ɨ���4��
	
	P1=0xFF;//ȫ��1
	P1_1=0;//ɨ���3��
	if(P1_7==0){delay_ms(10);while(P1_7==0);delay_ms(10);KeyNumber=3;}//ɨ���1��
	if(P1_6==0){delay_ms(10);while(P1_6==0);delay_ms(10);KeyNumber=7;}//ɨ���2��
	if(P1_5==0){delay_ms(10);while(P1_5==0);delay_ms(10);KeyNumber=11;}//ɨ���3��
	if(P1_4==0){delay_ms(10);while(P1_4==0);delay_ms(10);KeyNumber=15;}//ɨ���4��
	
	P1=0xFF;//ȫ��1
	P1_0=0;//ɨ���4��
	if(P1_7==0){delay_ms(10);while(P1_7==0);delay_ms(10);KeyNumber=4;}//ɨ���1��
	if(P1_6==0){delay_ms(10);while(P1_6==0);delay_ms(10);KeyNumber=8;}//ɨ���2��
	if(P1_5==0){delay_ms(10);while(P1_5==0);delay_ms(10);KeyNumber=12;}//ɨ���3��
	if(P1_4==0){delay_ms(10);while(P1_4==0);delay_ms(10);KeyNumber=16;}//ɨ���4��
	
	return KeyNumber;

}