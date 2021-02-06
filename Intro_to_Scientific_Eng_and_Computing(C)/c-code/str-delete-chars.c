#include <stdio.h>
#include <stdlib.h>

int main(){

    char str[50] = "helloXX worldXXX";
    int left = 0;
    int right = 0;
    while(str[right] != '\0') {
        if (str[right] != 'X') {
            str[left] = str[right];
            ++left;
        }
        ++right;
    }
    str[left] = '\0';
    printf("%s\n", str);

    return 0;
}

    // char str[100] = "Hello world";
    // int a = 0;
    // a = scanf("%s", str);
    // printf("%s and %d \n", str, a);


    // FILE* fptr = NULL;
    // if((fptr = fopen("new.txt","w")) == NULL ) {
    //     puts("something wrong");
    //     return EXIT_FAILURE;
    // } else {
    //     for (int i = 0; i < 5; i++)
    //     {
    //         fprintf(fptr, "%s %d\n", "hello world", i);
    //     }
    //     fclose(fptr);
    // }
    // if((fptr = fopen("new.txt","r")) == NULL ) {
    //     puts("something wrong");
    //     return EXIT_FAILURE;
    // } else {
    //     for (int i = 0; i < 5; i++)
    //     {   
    //         int num = 0;
    //         char str[50];
    //         char str2[50];
    //         fscanf(fptr, "%s %s %d\n", str, str2, &num);
    //         printf("%s %s and %d\n", str, str2, num);
    //     }
    //     fclose(fptr);
    // }