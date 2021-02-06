#include <stdio.h>
#define SIZE 80
// When you do assignment, it returns assigned value !!!
int main() {
    int c = 12;
    int d = 12;
    printf("%d\n",(c = getchar())); // getchar() takes a char and returns its ASCII value as integer !!!
    while ((d = getchar()) != '\n' && d != EOF);
    printf("%c\n",(d = getchar())); // getchar() takes a char and returns its ASCII value as integer !!!
    return 0;
}