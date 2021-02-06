#include <stdio.h> // fgets
#include <stdlib.h> // atoi
#include <string.h> // strlen, strcpy
/* 
** Usage of atoi
*/
int main() {
    int val = 0;
    //char str[20] = "98993489";
    //char str[20] = "itu.edu.tr";
    //char str[20] = "it61u.ed23u.tr65";
    char str[20] = "46itu.edu.tr";

    // First get the sentence from the user using fgets() function.
    val = atoi(str);
    printf("sentence is: %d", val);
    
    return 0;
}

/* 
** Length of a string---- strcpy, strlen implementations.
*/
// void my_strcpy(char* dest, char* source) {
//     char* ptr = source;
//     char* dest_ptr = dest;
//     while(*ptr != '\0') {
//         *dest_ptr = *ptr;
//         ++ptr;
//         ++dest_ptr;
//     }
//     *dest_ptr = '\0';
// }
// int my_strlen(char* source) {
//     char* ptr = source;
//     int len = 0;
//     while(*ptr != '\0') {
//         ++ptr;
//         ++len;
//     }
//     return len;
// }

// int main() {
//     char sentence[20];
//     char copy[20];

//     // First get the sentence from the user using fgets() function.
//     fgets(sentence, 20, stdin);
//     printf("sentence is: %s", sentence);
//     // Print the length of the string using strlen().
//     int length_of_sentence = my_strlen(sentence);
//     printf("This is my length: %d\n", length_of_sentence);
//     // Copy the sentence and print the copied one.
//     //strcpy(copy, sentence);
//     my_strcpy(copy, sentence);
//     printf("copy is: %s", sentence);
//     return 0;
// }

/* 
** Upper case format
*/
// int main() {
//     char str[20];
//     char* ptr = NULL;
//     int diff = 'a' - 'A';

//     // First get the sentence from the user using fgets() function.
//     fgets(str, 20, stdin);
//     printf("%s", str);
//     // Then change the lower case characters to upper case characters.
//     ptr = str;
//     while (*ptr != '\0') {
//         if (*ptr <= 'z' && *ptr >= 'a') {
//             *ptr = *ptr - diff;
//         }
//         ++ptr;
//     }
//     ptr = str;
//     while (*ptr != '\0') {
//         printf("%c", *ptr);
//         ++ptr;
//     }
//     return 0;
// }

/* 
** Seperate the sentence into phrases
*/
// DEFAULT separator is ' '
// void split(char* ptr) {
//     while(*ptr != '\0') {
//         if(*ptr != ' ') {
//             printf("%c", *ptr);
//         }
//         else{
//             printf("\n");
//         }
//         ++ptr;
//     }
// }
// int main() {
//     char* sentence = "What a wonderful day!";
    
//     printf("Sentence is %s \n", sentence);
//     // Print each word of the sentence seperately.
//     split(sentence);

//     return 0;
// }


/* 
** Address of an Array ALSO REVERSE STRING*******!!!!!!!!
*/
// int main() {
//     char word[15];
//     char* ptr = &word[0];
//     //char* ptr = &(*(word + 0));
//     //char* ptr = word;
//     int i = 0;

//     printf("Enter a word: ");
//     scanf("%s", word);

//     // first print the word using the array itself.
//     while(word[i] != '\0') {
//         printf("%c", word[i]);
//         ++i;
//     }
//     // second print the word
//     // using the address of the array stored in a pointer.
//     printf("\n%s\n", word);

//     // Then print the reverse of the word
//     // using the address of the array stored in a pointer.
//     printf("reverse:\n");
//     //printf("%s", ptr);

//     while(*ptr != '\0') {
//         ++ptr;
//     }
//     --ptr;
//     while(ptr != word) {
//         printf("%c", *ptr);
//         --ptr;
//     }
//     return 0;
// }

/* 
** An Array of Chars
*/

// int main() {
//     char word[] = {'D', 'a', 'r', 'l', 'i', 'n', 'g', '!', '\0'};
//     int i = 0;
//     // first print each character using %c.
//     while (word[i] != '\0') {
//         printf("%c", word[i]);
//         ++i;
//     }
//     printf("\n");
//     // then print the word as a string using %s.
//     printf("%s", word);
//     return 0;
// }