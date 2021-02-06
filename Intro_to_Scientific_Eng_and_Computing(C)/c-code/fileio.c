#include <stdio.h>
#include <stdlib.h>

#define SIZE 80

int main() {
    unsigned int account; 
    char name[30];  
    double balance; 
    FILE *fptr = NULL;
    
    if ((fptr = fopen("clients.txt","w")) == NULL) {
        puts("something went wrong while opening file");
        return EXIT_FAILURE;
    } else {
        puts("enter a. num, name and balance");
        puts("enter EOF to end input");
        printf("enter: ");
        while ((fscanf(stdin, "%d%29s%lf", &account, name, &balance)) == 3)
        {
            fprintf(fptr, "%d %s %.2f\n", account, name, balance);
            printf("enter: ");
        }
        fclose(fptr);
    }
    return EXIT_SUCCESS;
}