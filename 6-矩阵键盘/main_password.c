
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
                my_code[6] = '\0'; // 确保字符串正确终止
                if (strcmp((char *)my_code, (char *)password) == 0)
                {
                    lcd1602_show_string(13, 0, "   "); // 清空原来的ERR
                    lcd1602_show_string(14, 0, "OK");
                    clear_password(&start, my_code); // 成功了也要清零！
                }
                else
                {
                    lcd1602_show_string(13, 0, "ERR"); // 错误之后，清零重新输入
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
                lcd1602_show_string(start++, 1, lcd1602_num_2_str_0_9(key)); // 每按下一次，显示光标就左移一次
                my_code[start - 7] = key + '0';                              // 注意这里应该是start-7，因为start已经自增了
            }
            if (start == 12)
            { // 到达12位自动确认,注意这里是单独的if判断，不是else if

                my_code[6] = '\0'; // 添加字符串结束符
                if (strcmp((char *)my_code, (char *)password) == 0)
                {
                    lcd1602_show_string(13, 0, "   "); // 清空原来的ERR
                    lcd1602_show_string(14, 0, "OK");
                    clear_password(&start, my_code); // 成功了也要清零！
                }
                else
                {
                    lcd1602_show_string(13, 0, "ERR"); // ERR比OK长，会自己覆盖
                    clear_password(&start, my_code);
                }
            }
        }
    }
}