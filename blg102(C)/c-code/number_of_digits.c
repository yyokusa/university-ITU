#include <stdio.h>
#include <math.h>

int get_no_of_digits(int number);
int get_first_digit(int number);

int main(int argc, char const *argv[])
{
    int number = 650;
    printf("num of digits of %d is %d\n", number, get_no_of_digits(number));
    printf("num of digits of %d is %d\n", 745654, get_no_of_digits(745654));
    printf("num of digits of %d is %d\n", 85431, get_no_of_digits(85431));
   
    printf("get_first_digit %d is %d\n", number, get_first_digit(number));
    printf("get_first_digit %d is %d\n", 745654, get_first_digit(745654));
    printf("get_first_digit %d is %d\n", 85431, get_first_digit(85431));

    return 0;
}


int get_no_of_digits(int number)
{
    int digits = 0;
    while(number)
    {
        number /= 10;
        ++digits;
    }
    return digits;
}

int get_first_digit(int number)
{
    int x = number;
    while(x > 9)
    {
        x /= 10;
    }
    // int digits = log10(number);
    // int first_digit = number / pow(10, digits);
    // return first_digit;

    return x;
}