#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 20

void get_uppercase(char *sentence, int size);



int main()
{

    char str[SIZE];
    char *ptr = str;
    // char *ptr;
    int diff = 'a' - 'A';

    printf("Enter the sentence: ");
    fgets(str, SIZE,stdin);
    // get_uppercase(str, SIZE);
    get_uppercase(ptr, SIZE);
    printf("new sentence is: %s", ptr);

    return 0;
}

void get_uppercase(char *sentence, int size)
{
    int i = 0;
    while (i != size)
    {
        char c = sentence[i]; 
        if (c >= 'a' && c <= 'z')
        {
            sentence[i] = c - ('a' - 'A');
        }
        ++i;
    }
    // putchar('\n');
    fputc('\n', stdout);
}