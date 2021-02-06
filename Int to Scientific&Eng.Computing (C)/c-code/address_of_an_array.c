#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 15

int main()
{
    char word[SIZE];
    char *ptr = &word[0];
    // char *ptr = &(*(word+ 0));
    // char *ptr = word;
    int i;

    printf("Enter a word: ");
    scanf("%s", word);

    //First print the word using the array itself
    printf("%s\n", word);

    //Second print the word using the address 
    //of the array stored in a pointer
    printf("%s\n", ptr);
    
    //Then print the reverse of the word
    //using the address of the array stored in a pointer
    i = strlen(word);
    while(i--)
    {
        printf("%c", ptr[i]);
        // printf("i: %d\n", i);
    }
    printf("\n");

    return 0;
}

void generate_random_array(char *string, int size)
{
    srand(time(0));
    for (size_t i = 0; i < size - 1; i++)
    {
        int randChar = rand() % 'A' + 24;
        string[i] = randChar;
    }
}
void print_array_cbyc(char *string, int size)
{
    // for (size_t i = 0; i < size; i++)
    // {
    //     fprintf(stdout, "%c ", string[i]);
    // }
    int i = 0;
    char c;
    while( (c = string[i++]) != '\0')
    {
        printf("%c", c);
    }
    fprintf(stdout, "\n");
}
void print_array_s(char *string, int size)
{
    fprintf(stdout, "%s\n", string);
}