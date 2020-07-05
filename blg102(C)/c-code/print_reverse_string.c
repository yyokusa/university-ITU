#include <stdio.h>
#define SIZE 80

void reverse(char* ptr) {
    int count = 0;
    while(*ptr != '\0') {
        count++;
        ptr++;
    }
    ptr--;
    count--;
    for(int begin = count; begin >= 0; begin--) {
        putchar(*ptr);  //putchar takes integers which are ASCII codes of chars
        ptr--;
    }
}

int main() {
    char sentence[SIZE];
    puts("Enter line of text: ");
    
    // char c;
    // int i = 0;
    // while ((c = getchar()) != '\n' && c != EOF) {sentence[i++] = c;}
    
    // fgets(sentence, SIZE, stdin);
    puts("The line printed backwards is ");
    reverse(sentence);
    return 0;
}