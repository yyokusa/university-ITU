// baykar oop mülakat sorusu
#include <stdio.h>
#include <stdlib.h>

void fibonacci(int curr_num, int fib1, int fib2, int target);

int main(int argc, char **argv)
{

    int num = 0;
    printf("Enter target num: ");
    scanf("%d", &num);
    fibonacci(0, 0, 1, num);

    return 0;
}

void fibonacci(int curr_num, int fib1, int fib2, int target)
{
    if (curr_num == target)
    {
        printf("%d th fibonacci number is %d\n", curr_num, fib1);
        return;
    }
    printf("%d th fibonacci number is %d\n", curr_num, fib1);
    int new_number = fib1 + fib2;
    fib1 = fib2;
    fib2 = new_number;
    fibonacci(++curr_num, fib1, fib2, target);
}
