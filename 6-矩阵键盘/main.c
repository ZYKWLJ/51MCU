#include "lcd1602.h"
#include "matrix.h"

void main()
{
    unsigned char key = 0;
    lcd1602_init();
    lcd1602_show_string(0, 0, "MatrixKey:");
    lcd1602_show_string(0, 1, "Input:");
    lcd1602_show_string(6, 1, "00");
    while (1)
    {
        key = matrixKey();
        if (key)
        {
            lcd1602_show_string(6, 1, lcd1602_num_2_str(key));
        }
    }
}
