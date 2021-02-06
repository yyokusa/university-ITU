#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
// void generate_random_array(char *string, int size);
void print_array_cbyc(char *string, int size);
void print_array_s(char *string, int size);

int main()
{
    // char string[SIZE] = {'\0'};
    // generate_random_array(string, SIZE);
    char string[SIZE] = "hello wor";
    print_array_cbyc(string, SIZE);
    print_array_s(string, SIZE);
    return 0;
}

// void generate_random_array(char *string, int size)
// {
//     srand(time(0));
//     for (size_t i = 0; i < size - 1; i++)
//     {
//         char randChar = rand() % 'A' + 24;
//         string[i] = randChar;
//     }
// }
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