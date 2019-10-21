#include "helper.h"
int helper::calc_decimal_digits(char* target)
{
    int temp = 0;
    for (int i = 0; ; i++)
    {
        char temp_char = target[i];
        if ((temp_char < '.' || temp_char > '9') && temp_char != '/')
        {
            break;
        }
        temp++;
    }
    return temp;
}