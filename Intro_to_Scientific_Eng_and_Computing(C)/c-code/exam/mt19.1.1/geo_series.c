#include <stdio.h>


int main(int argc, char const *argv[])
{
    /* code */
    int n;
    double result = 1.0;
    printf("Enter n: "); // prompt
    scanf("%d", &n);  // n > 2
    
    if (1 == n % 2) {
        for (int i = 2; i <= n; i++) // n = 3, 4, 5...
        {
            if (1 == i % 2)
            {
                result = result + (1.0 / (i * (i-1)));            
            }
        }
    }
    else 
    {
        for (int i = 3; i < n; i++) // n = 3, 4, 5...
        {
            if (1 == i % 2)
            {
                result = result + (1.0 / (i * (i-1)));            
            }
        }
        result = result + 1.0 / (n);
    }
    printf("%f\n", result);
    return 0;
}
