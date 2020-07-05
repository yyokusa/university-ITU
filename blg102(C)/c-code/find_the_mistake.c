#include <stdio.h>

int main(int argc, char const *argv[])
{
    double total = 0;
    int x1 = 0;
    printf("Please enter a number: ");
    scanf("%d", &x1);
    total = total + x1;
    printf("Please enter another number: ");
    int x2;
    scanf("%d", &x2);
    total = total + x2;
    double average = (double) total / (double) 2;
    printf("The average of the two numbers is %lf\n", average); 
    return 0;
}



// int total;
// int x1;
// printf("Please enter a number: ");
// scanf("%d", &x1);
// total = total + x1;
// printf("Please enter another number: ");
// int x2;
// scanf("%d", &x2);
// total = total + x1;
// double average = total / 2;
// printf("The average of the two numbers is %d\n", average);