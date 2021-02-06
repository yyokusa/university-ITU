#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int num;
    FILE* fptr;

    fptr = fopen("/Users/yasinyokus/Desktop/BLG102E(C)/c-programs/file_io/file_io.txt","w");
    if(fptr == NULL) {
        printf("error opening file");
        exit(1);
    }
    printf("Enter a number:\n");
    scanf("%d", &num);

    fprintf(fptr, "%d", num);

    fclose(fptr);

    return 0;
}