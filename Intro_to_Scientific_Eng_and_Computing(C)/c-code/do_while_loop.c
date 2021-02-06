#include <stdio.h>

int main(int argc, char const *argv[])
{
    char answer = 'Y';
    char c = 'Y';
    int number;
    do
    {
        printf("Enter a number: ");
        scanf("%d", &number);
        for (int i = 1; i <= 10; i++)
        {
            printf("%d  ", number * i);
        }
        printf("\nTry another?\nY for yes N for no: ");
        // BUFFER DA \n kalıyor scanf de direk char diye onu okuyor, engellemek için bunu kullanabilirsin
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        scanf("%c", &answer);
    } while (answer != 'N');

    return 0;
}
