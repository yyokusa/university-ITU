#include <stdio.h> // fgets
#include <stdlib.h> // atoi
#include <string.h> // strlen, strcpy

// void memcpy1(char* dst, char* src, size_t size) {
//     if (dst == src) {
//         printf("errror\n");
//         return;
//     }
//     char* ptr = src;
//     while (*ptr != '\0') {
//         *dst++ = *ptr++;
//     }
//     *dst = '\0';
// }

// int main() {

//     char arr[100] = "hello world from the other side";
//     char arr2[100] = "this is new";
//     printf("old: %s\n", arr);
//     memcpy1(arr, arr2, sizeof(char) * strlen(arr2));
//     printf("new: %s\n", arr);
//     return 0;
// }





// const char* char_in_str(char* str, char c) {
// //const char* char_in_str(char* str, int c) {
//     //printf("%c\n", c);
//     //printf("%d\n", c);
//     char *ptr = str;
//     while(ptr!='\0'){
//         if (*ptr == c) {
//             return ptr;
//         }
//         ++ptr;
//     }
//     return NULL;
// }

// int main() {

//     char arr[100] = "hello world from the other side";
//     const char* ptr = char_in_str(arr, 'm');
//     printf("%s\n", ptr);
//     return 0;
// }



// #define SIZE 20
// void my_gets(char* ptr, int size) {
//     char c;
//     int i = 0;
//     while((c = getchar()) != '\n' && i < size) {
//         *ptr = c;
//         ++ptr;
//         ++i;
//     }
//     *ptr = '\0';
// }
// void my_puts(char* ptr, int size) {
//     int i = 0;
//     while(*ptr != '\0' && i < size) {
//         printf("%c",*ptr);
//         ++ptr;
//         ++i;
//     }
//     printf("\n");
// }

// int main() {
//     char arr[SIZE];
//     my_gets(arr, SIZE);
//     my_puts(arr, SIZE);
//     //printf("%s\n", arr);

//     return 0;
// }

