#include <stdio.h>
#include <string.h>
// #include <stdlib.h>
// #include <time.h>

_Bool check_sum(const char digits[], int size);
void fix_num(const char digits[], int size);
#define SIZE 16

int main()
{
    const char digits[16] = "4123175904981754";
    printf("res: %d\n", check_sum(digits, SIZE));
    const char missing_digits[16] = "41231?5904981754";
    fix_num(digits, SIZE);
    return 0;
}

void fix_num(const char digits[], int size)
{
    char newDigits[size];
    // int k = 0;
    // for (k = 0; k < size; k++)
    // {
    //     newDigits[k] = digits[k];
    // }
    // newDigits[k] = '\0';
    strcpy(newDigits, digits);
    printf("fixed string: %s\n\n", newDigits);
    for (int i = 0; i < size; i++)
    {
        if (newDigits[i] == '?')
        {
            for (int j = 0; j < 10; j++)
            {
                newDigits[i] = j + '0';
                if (check_sum(newDigits, 16))
                {
                    printf("fixed string: %s\n\n", newDigits);
                    break;
                }
            }
            break;
        }
    }
}

_Bool check_sum(const char digits[], int size)
{
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        int temp = digits[i] - '0';
        if (i % 2 == 1)
        {
            int temp2 = 2 * temp;
            if (temp2 > 9)
            {
                temp2 = temp2 - 9;
            }
            result += temp2;
        }
        result += temp;
    }
    return !(result % 10);
}