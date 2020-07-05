#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void coppy(char* dest, const char* source, int n);
int find_nullchar_index(const char* str);


int main()
{
    char full_email[100];
    full_email[0] = '\0';
    char* name = "yasin";
    char* surname = "yokus";
    char* year = "2019";
    char* fixed = "@itu.edu.tr";
    coppy(full_email, name, 1);
    coppy(full_email, surname, 5);
    coppy(full_email, year, 4);
    coppy(full_email, fixed, 11);
    printf("%s\n", full_email);
    return 0;
}


void coppy(char* dest, const char* source, int n) {
    int k = find_nullchar_index(dest);
    int i = 0;
    while(i < n && source[i] != '\0') {
        dest[i + k] = source[i];
        ++i;
    }
    dest[i + k] = '\0';
}

int find_nullchar_index(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        ++i;
    }
    return i;
}











// char* first_suggestion(char full_email[], char* name, char* surname, char* year) {
//     const char* fixed = "@itu.edu.tr";
    
//     full_email[0] = *(name + 0);
    
//     int i = 0;
//     int counter = 0;
//     while (*(surname + i) != '\0') {
//         *(full_email + i + 1) = *(surname + i);
//         ++i;
//         ++counter;
//     }
//     i = 0;
//     while (*(year + i) != '\0') {
//         *(full_email + i + 1 + counter) = *(year + i);
//         ++i;
//     }
//     i = 0;
//     while (*(fixed + i) != '\0') {
//         *(full_email + i + counter) = *(fixed + i);
//         ++i;
//     }
//     *(full_email + i + counter + 12) = '\0';

//     return full_email;

// }