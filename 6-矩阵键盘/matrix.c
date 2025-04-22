#include "matrix.h"

unsigned char matrixKey(){
	
	unsigned char KeyNumber=0;
	P1=0xFF;//全置1
	P1_3=0;//扫描第1列
	if(P1_7==0){delay_ms(10);while(P1_7==0);delay_ms(10);KeyNumber=1;}//扫描第1行
	if(P1_6==0){delay_ms(10);while(P1_6==0);delay_ms(10);KeyNumber=5;}//扫描第2行
	if(P1_5==0){delay_ms(10);while(P1_5==0);delay_ms(10);KeyNumber=9;}//扫描第3行
	if(P1_4==0){delay_ms(10);while(P1_4==0);delay_ms(10);KeyNumber=13;}//扫描第4行
	
	P1=0xFF;//全置1
	P1_2=0;//扫描第2列
	if(P1_7==0){delay_ms(10);while(P1_7==0);delay_ms(10);KeyNumber=2;}//扫描第1行
	if(P1_6==0){delay_ms(10);while(P1_6==0);delay_ms(10);KeyNumber=6;}//扫描第2行
	if(P1_5==0){delay_ms(10);while(P1_5==0);delay_ms(10);KeyNumber=10;}//扫描第3行
	if(P1_4==0){delay_ms(10);while(P1_4==0);delay_ms(10);KeyNumber=14;}//扫描第4行
	
	P1=0xFF;//全置1
	P1_1=0;//扫描第3列
	if(P1_7==0){delay_ms(10);while(P1_7==0);delay_ms(10);KeyNumber=3;}//扫描第1行
	if(P1_6==0){delay_ms(10);while(P1_6==0);delay_ms(10);KeyNumber=7;}//扫描第2行
	if(P1_5==0){delay_ms(10);while(P1_5==0);delay_ms(10);KeyNumber=11;}//扫描第3行
	if(P1_4==0){delay_ms(10);while(P1_4==0);delay_ms(10);KeyNumber=15;}//扫描第4行
	
	P1=0xFF;//全置1
	P1_0=0;//扫描第4列
	if(P1_7==0){delay_ms(10);while(P1_7==0);delay_ms(10);KeyNumber=4;}//扫描第1行
	if(P1_6==0){delay_ms(10);while(P1_6==0);delay_ms(10);KeyNumber=8;}//扫描第2行
	if(P1_5==0){delay_ms(10);while(P1_5==0);delay_ms(10);KeyNumber=12;}//扫描第3行
	if(P1_4==0){delay_ms(10);while(P1_4==0);delay_ms(10);KeyNumber=16;}//扫描第4行
	
	return KeyNumber;

}