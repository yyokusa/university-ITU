#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void seperate_sentence(char *sentence, int size);

int main()
{
    char *sentence = "What a beautiful day!";
    char *word = sentence;
    int i = 1;
    char *ptr;

    printf("Sentence is %s \n", sentence);

    seperate_sentence(sentence, strlen(sentence));

    return 0;
}

void seperate_sentence(char *sentence, int size)
{
    int i = 0;
    while (i != size)
    {
        char c = sentence[i++]; 
        if (c != ' ')
        {
            putchar(c);
        }
        else
        {
           putchar('\n');
        }
    }
    putchar('\n');
}