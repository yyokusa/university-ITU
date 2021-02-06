#include <stdio.h>

int main(int argc, char const *argv[])
{
    double pi = 0;
    double circle_area;
    double square_area;
    printf("Enter circle area: ");
    scanf("%lf", &circle_area);  
    printf("Enter square area: ");  
    scanf("%lf", &square_area);    
    pi = 4 * (circle_area / square_area);

    printf("pi aprox: %.5lf",pi);  
    
    return 0;
}
