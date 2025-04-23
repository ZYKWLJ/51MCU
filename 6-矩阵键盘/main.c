
#include "lcd1602.h"
#include "matrix.h"
#include <string.h>

// ���㺯��
void clear_password(unsigned char *start, unsigned char *my_code)
{
    unsigned char i = 0; // ��i�Ķ����Ƶ�������ͷ
    lcd1602_show_string(6, 1, "------");
    *start = 6;
    for (i = 0; i < 6; i++)
    {
        my_code[i] = 0;
    }
}

void main()
{
    // �����б��������Ƶ�������ͷ
    unsigned char key = 0;
    unsigned char start = 6; // ��ȥ֮ǰ��INPUT:
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
        if (key) // 0~9���룬10Ϊȷ�ϣ�11λΪɾ�������಻������
        {
            if (key == 10) // ȷ�ϼ�������δ����12�Լ�ȷ�ϣ���һ���ᱨ��
            {
                my_code[6] = '\0'; // ȷ���ַ�����ȷ��ֹ����ʵ�ϣ�����һ����error�ģ���Ϊһ������6�Σ���ֱ���ж��ˣ������л���������
                if (strcmp((char *)my_code, (char *)password) == 0)
                {
                    lcd1602_show_string(11, 0, "   "); // ���ԭ����ERR
                    lcd1602_show_string(14, 0, "OK");
                    clear_password(&start, my_code); // �ɹ���ʧ�ܼ�ʱ���㣬������Ҳ����
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

                    lcd1602_show_string(11, 0, error_str); // ����֮��������������
                    error_count++;
                    clear_password(&start, my_code);
                }
            }
            else if (key == 11) // ȡ����
            {
                if (start > 6)
                {
                    lcd1602_show_string(--start, 1, "-");
                    my_code[start - 6] = 0;
                }
            }
            else if (key > 11)
            { // ����12�Ժ�ļ���û���κ���������
                continue;
            }
            else if (start < 12) // ��ֹ����Խ��
            {
                unsigned char key_str[2];
                key_str[0] = key + '0'; // ������ת��Ϊ�ַ�
                key_str[1] = '\0';      // ����ַ���������
                lcd1602_show_string(start++, 1,key_str ); // ÿ����һ�Σ���ʾ��������һ��
                my_code[start - 7] = key + '0';                              // ע������Ӧ����start-7����Ϊstart�Ѿ�������
            }
            if (start == 12)
            { // ����12λ�Զ�ȷ��,ע�������ǵ�����if�жϣ�����else if

                my_code[6] = '\0'; // ����ַ���������
                if (strcmp((char *)my_code, (char *)password) == 0)
                {
                    lcd1602_show_string(11, 0, "     "); // ���ԭ����ERR
                    lcd1602_show_string(14, 0, "OK");//OK��ʾ��1s���Զ���ʧ
                    // ��ʾwelcome
                    lcd1602_show_string(0, 1, "                ");
                    lcd1602_show_string(0, 1, "welcome");
                    delay1000ms();
                    delay1000ms();
                    delay1000ms();
                   
                    //�ӳ�3s���ֿ�ʼ��������
                    lcd1602_show_string(11, 0, "     "); // ���ԭ����OK
                    lcd1602_show_string(0, 1, "                ");
                    lcd1602_show_string(0, 1, "Input:");
                    lcd1602_show_string(6, 1, "------");
                    clear_password(&start, my_code); // �ɹ���ҲҪ���㣡
                    error_count=0;
                }
                else
                {
                    char error_str[6];
                    error_str[0] ='E';  
                    error_str[1] ='R';  
                    error_str[2] ='R';  
                    error_str[3] =' ';
                    error_str[4] =++error_count+'0';  //��ʾʧ�ܴ���
                    error_str[5] ='\0';  
                    lcd1602_show_string(11, 0, error_str); // ����֮�������������� // ERR��OK�������Լ�����
                    clear_password(&start, my_code);
                }
            }
            if (error_count==error_max_times)
            { 
                int i=wait_times;//ÿ��һ�Σ�������1����ʱ��
                // C89Ҫ����������Ҫ�ں�����ͷ����������Ҫ�ѱ��������Ƶ�������ͷ
                wait_times=wait_times*2>99?99:wait_times*2;
                // i=wait_times;
                // i=i>99?99:i;//������99s�ĵȴ�ʱ��
                // total_error++;
                lcd1602_show_string(0, 1, "-----Locked-----");
                lcd1602_show_string(11, 0, "   ");//�Ƚ�֮ǰ��OK��ERR���
                while(i>0){
                    //���Ϸ���ʾ��ʱ��Ϣ������ʱ��
                    if(i<10){
                        char wait_str[3];
                        wait_str[0]=i+'0';
                        wait_str[1]='s';
                        wait_str[2]='\0';
                        lcd1602_show_string(14, 0,wait_str);
                    }else{
                        //��ʾ��λ��
                        char wait_str[4];
                        wait_str[0]=i/10+'0';
                        wait_str[1]=i%10+'0';
                        wait_str[2]='s';
                        wait_str[3]='\0';
                        lcd1602_show_string(13, 0,wait_str);
                    }
                    delay1000ms();//��ʱʱ�����ʱ����������ʾLocked
                    i--;
                }
                lcd1602_show_string(13, 0, "   ");//��֮ǰ�ļ�ʱ��Ϣ���
                lcd1602_show_string(0, 1, "                ");//�����һ�е���ס��Ϣ
                error_count=0;//���ô������
                lcd1602_show_string(0, 1, "Input:");
                lcd1602_show_string(6, 1, "------");//��ס��ʱ������ֿ��Կ�ʼ����
            }
        }
    }
}