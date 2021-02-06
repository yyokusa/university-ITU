#include <stdio.h>

#define SIZE 80

int main()
{
    char s[SIZE];
    int x = 0;
    double y;
    puts("Enter the values int and double like 44 25.0");
    scanf("%d %lf", &x,&y);
    sprintf(s, "integer:%6d\ndouble:%8.2f", x, y);
    puts("Printing s\n");
    printf("%s \n", s);
    
    puts("\nMultiplying x\n");
    x = x*2;
    printf("%d",x);
    sscanf(s, "integer:%d\ndouble:%lf", &x, &y);
    printf("\nThe string s has the values:\n%s\n",s);
    printf("The values x and y are:\n integer:%d and double %f\n",x ,y);
    printf("\nThe string s has the values:\n%s\n",s);

}