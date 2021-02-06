// Turn the given do while loop into while loop.
// Since do code block is guaranteed to be executed at least once in do while 
// we put that code also before the while block in the only while version.
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    double x = 0;
    double s;
    // do
    // {
    //     s = 1.0 / (1 + n * n);
    //     n++;
    //     x = x + s;
    //     // while ((c = getchar()) != '\n' && c != EOF)
    // } while (s > 0.01);

    s = 1.0 / (1 + n * n);
    n++;
    x = x + s;
    while (s > 0.01)
    {
        s = 1.0 / (1 + n * n);
        n++;
        x = x + s;
    }
    
    printf("n: %d\n", n);
    printf("x: %lf\n", x);
    printf("s: %lf\n", s);

    return 0;
}
