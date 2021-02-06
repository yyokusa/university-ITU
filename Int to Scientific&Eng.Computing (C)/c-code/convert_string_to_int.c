#include <stdio.h>
#include <stdlib.h>

#define SIZE 20


int main()
{
    char sentence1[SIZE] = "98993489";
    char sentence2[SIZE] = "itu.edu.tr";
    char sentence3[SIZE] = "itu94.edu.tr";
    char sentence4[SIZE] = "itu94.edu.tr16";
    char sentence5[SIZE] = "36itu94.edu.tr16";

    printf("atoi on sentence1: %d\n", atoi(sentence1));
    printf("atoi on sentence2: %d\n", atoi(sentence2));
    printf("atoi on sentence3: %d\n", atoi(sentence3));
    printf("atoi on sentence4: %d\n", atoi(sentence4));
    printf("atoi on sentence5: %d\n", atoi(sentence5));

    return 0;
}
