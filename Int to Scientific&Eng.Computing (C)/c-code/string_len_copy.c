#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 20

void get_uppercase(char *sentence, int size);

int main()
{

    char sentence[SIZE];
    char copy[SIZE];
    
    printf("Enter a str:\n" );
    fgets(sentence, SIZE, stdin);

    int slen = strlen(sentence);
    printf("len of the str: %d\n", slen);

    strcpy(copy, sentence);
    printf("copied str: %s\n", copy);

    return 0;
}
