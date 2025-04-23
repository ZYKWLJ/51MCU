
#include "lcd1602.h"
#include "matrix.h"
#include <string.h>

// 清零函数
void clear_password(unsigned char *start, unsigned char *my_code)
{
    unsigned char i = 0; // 将i的定义移到函数开头
    lcd1602_show_string(6, 1, "------");
    *start = 6;
    for (i = 0; i < 6; i++)
    {
        my_code[i] = 0;
    }
}

void main()
{
    // 将所有变量定义移到函数开头
    unsigned char key = 0;
    unsigned char start = 6; // 除去之前的INPUT:
    unsigned char password[7] = "123456";
    unsigned char my_code[7] = {0};
    unsigned char error_count=0;
    const unsigned char error_max_times=3;
    unsigned char wait_times=2;
    // unsigned char total_error=1;
    lcd1602_init();
    lcd1602_show_string(0, 0, "Password:");
    lcd1602_show_string(0, 1, "Input:");
    lcd1602_show_string(6, 1, "------");

    while (1)
    {
        key = matrixKey();
        if (key) // 0~9密码，10为确认，11位为删除，其余不起作用
        {
            if (key == 10) // 确认键，可以未到达12自己确认，但一定会报错
            {
                my_code[6] = '\0'; // 确保字符串正确终止，事实上，这里一定是error的，因为一旦到达6次，就直接判断了，不会有机会来这里
                if (strcmp((char *)my_code, (char *)password) == 0)
                {
                    lcd1602_show_string(11, 0, "   "); // 清空原来的ERR
                    lcd1602_show_string(14, 0, "OK");
                    clear_password(&start, my_code); // 成功了失败计时清零，输入区也清零
                    error_count=0;
                }
                else
                {
                    char error_str[6];
                    error_str[0] ='E';  
                    error_str[1] ='R';  
                    error_str[2] ='R';  
                    error_str[3] =' ';
                    error_str[4] =error_count+'0';  
                    error_str[5] ='\0';  

                    lcd1602_show_string(11, 0, error_str); // 错误之后，清零重新输入
                    error_count++;
                    clear_password(&start, my_code);
                }
            }
            else if (key == 11) // 取消键
            {
                if (start > 6)
                {
                    lcd1602_show_string(--start, 1, "-");
                    my_code[start - 6] = 0;
                }
            }
            else if (key > 11)
            { // 按下12以后的键，没有任何其他功能
                continue;
            }
            else if (start < 12) // 防止数组越界
            {
                unsigned char key_str[2];
                key_str[0] = key + '0'; // 将数字转换为字符
                key_str[1] = '\0';      // 添加字符串结束符
                lcd1602_show_string(start++, 1,key_str ); // 每按下一次，显示光标就左移一次
                my_code[start - 7] = key + '0';                              // 注意这里应该是start-7，因为start已经自增了
            }
            if (start == 12)
            { // 到达12位自动确认,注意这里是单独的if判断，不是else if

                my_code[6] = '\0'; // 添加字符串结束符
                if (strcmp((char *)my_code, (char *)password) == 0)
                {
                    lcd1602_show_string(11, 0, "     "); // 清空原来的ERR
                    lcd1602_show_string(14, 0, "OK");//OK显示了1s后自动消失
                    // 显示welcome
                    lcd1602_show_string(0, 1, "                ");
                    lcd1602_show_string(0, 1, "welcome");
                    delay1000ms();
                    delay1000ms();
                    delay1000ms();
                   
                    //延迟3s后又开始重新输入
                    lcd1602_show_string(11, 0, "     "); // 清空原来的OK
                    lcd1602_show_string(0, 1, "                ");
                    lcd1602_show_string(0, 1, "Input:");
                    lcd1602_show_string(6, 1, "------");
                    clear_password(&start, my_code); // 成功了也要清零！
                    error_count=0;
                }
                else
                {
                    char error_str[6];
                    error_str[0] ='E';  
                    error_str[1] ='R';  
                    error_str[2] ='R';  
                    error_str[3] =' ';
                    error_str[4] =++error_count+'0';  //显示失败次数
                    error_str[5] ='\0';  
                    lcd1602_show_string(11, 0, error_str); // 错误之后，清零重新输入 // ERR比OK长，会自己覆盖
                    clear_password(&start, my_code);
                }
            }
            if (error_count==error_max_times)
            { 
                int i=wait_times;//每错一次，就增加1倍延时！
                // C89要求所有声明要在函数开头，所以这里要把变量定义移到函数开头
                wait_times=wait_times*2>99?99:wait_times*2;
                // i=wait_times;
                // i=i>99?99:i;//不超过99s的等待时间
                // total_error++;
                lcd1602_show_string(0, 1, "-----Locked-----");
                lcd1602_show_string(11, 0, "   ");//先将之前的OK或ERR清空
                while(i>0){
                    //右上方显示延时信息，倒计时！
                    if(i<10){
                        char wait_str[3];
                        wait_str[0]=i+'0';
                        wait_str[1]='s';
                        wait_str[2]='\0';
                        lcd1602_show_string(14, 0,wait_str);
                    }else{
                        //显示两位数
                        char wait_str[4];
                        wait_str[0]=i/10+'0';
                        wait_str[1]=i%10+'0';
                        wait_str[2]='s';
                        wait_str[3]='\0';
                        lcd1602_show_string(13, 0,wait_str);
                    }
                    delay1000ms();//延时时，这个时候输入区显示Locked
                    i--;
                }
                lcd1602_show_string(13, 0, "   ");//将之前的计时信息清空
                lcd1602_show_string(0, 1, "                ");//清空上一行的锁住信息
                error_count=0;//重置错误次数
                lcd1602_show_string(0, 1, "Input:");
                lcd1602_show_string(6, 1, "------");//锁住的时间过后，又可以开始输入
            }
        }
    }
}