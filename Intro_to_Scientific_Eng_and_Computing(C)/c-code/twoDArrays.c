#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    char *days[] = {" Saturday.\n", " Sunday.\n", " Monday.\n", " Tuesday.\n", " Wednesday.\n", " Thursday.\n", " Friday.\n"};

    for (int i = 0; i < 7; i++)
    {
        printf("%s", days[i]);
    }

    int i = 0;
    int j = 0;
    while (i < 7 && *days[i] != '\0')
    {
        printf("%c", *(days[i] + j));
        ++j;
        if (*(days[i] + j) == '\0')
        {
            //printf("\n");
            ++i;
            j = 0;
        }
    }
}