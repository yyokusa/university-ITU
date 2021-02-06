#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 60

typedef struct info
{
    char fname[20];
    char lname[20];
    int byear;
} Info;

void generate_email(Info *info, char email[], int case_no);
char* itoa(int num, char* str, int base);
void reverse_string(char str[], int len);
void swap(char *a, char *b);
void find_substring(char* dest, char* source, int start, int end, int size) ;

int main()
{
    int email_type = 0;
    char email[60] = {'\0'};
    Info info;

    fprintf(stdout, "Please enter your name, surname and birth year\n");
    fscanf(stdin, "%s %s %d", info.fname, info.lname, &(info.byear));

    fprintf(stdout, "what kind of email do you want to generate?\n");
    fprintf(stdout, "1 - Initial of name + surname + last 2 digits of the byear --> fhurel@itu.edu.tr\n");
    fprintf(stdout, "2 - First two from the initial name + First two from the last name + random number(4 digit) --> fehu8245@itu.edu.tr\n");
    fprintf(stdout, "3 - Surname + Name + byear --> hurelfaridun1951@itu.edu.tr\n");
    fscanf(stdin, "%d", &email_type);

    switch (email_type)
    {
    case 1:
        generate_email(&info, email, 1);
        break;
    case 2:
        generate_email(&info, email, 2);
        break;
    case 3:
        generate_email(&info, email, 3);
        break;
    default:
        fprintf(stdout, "Something went wrong!\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Generated email:\n%s\n", email);
    return EXIT_SUCCESS;
}


void generate_email(Info *info, char email[], int email_type)
{
    switch (email_type)
    {
        case 1:
        {
            //https://stackoverflow.com/questions/92396/why-cant-variables-be-declared-in-a-switch-statement
            char *ptr = NULL;
            ptr = email;
            char dest[20] = {'\0'};
            find_substring(dest, (info->fname), 0, 0, 20);
            strcat(email, dest);
            ptr += 1;
            char last_name[20];
            strcpy(last_name, (info->lname));
            strcat(ptr, last_name);
            ptr += strlen(last_name);
            char num_to_str[3];
            itoa((info->byear) % 100, num_to_str, 10);
            strcat(ptr, num_to_str);
            ptr += 2;
            strcat(ptr, "@itu.edu.tr");
            break;
        }
        case 2:
            {
                char dest[20] = {'\0'};
                find_substring(dest, (info->fname), 0, 1, 20);
                strcat(email, dest);
                find_substring(dest + 2, (info->lname), 0, 1, 20);
                strcat(email, dest + 2);
                int a = rand() % 10000;
                char num_to_str[5];
                itoa(a, num_to_str, 10);
                strcat(email + 4, num_to_str);
                strcat(email + 8, "@itu.edu.tr");
                break;
            }
        case 3:
            {
                int lname_len = strlen(info->lname);
                int fname_len = strlen(info->fname);
                strcat(email, info->lname);
                strcat(email + lname_len, info->fname);
                char num_to_str[5];
                itoa(info->byear, num_to_str, 10);
                int bday_len = strlen(num_to_str);
                strcat(email + lname_len + fname_len, num_to_str);
                strcat(email + lname_len + fname_len + bday_len, "@itu.edu.tr");
                break;
            }
        default:
            fprintf(stdout, "Something went while generating!\n");
            break;
    }
}



char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
  
    /* A zero is same "0" string in all base */
    if (num == 0) {
        str[i] = '0';
        str[i + 1] = '\0';
        return str;
    }
  
    /* negative numbers are only handled if base is 10 
       otherwise considered unsigned number */
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }
  
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        num = num/base;
    }
  
    /* Append negative sign for negative numbers */
    if (isNegative){
        str[i++] = '-';
    }
  
    str[i] = '\0';
 
    reverse_string(str, --i);
  
    return str;
}

void reverse_string(char str[], int size)
{
    for (size_t i = 0; i < size/2; i++)
    {
        swap(&str[i], &str[size - i]);
    }
}
void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

// start and end inclusive
void find_substring(char* dest, char* source, int start, int end, int size) 
{
    // if ((end - str + 1) > size || end > size)
    // {
    //     printf("can not extract sub str");
    //     exit(1);
    // }
    int dest_index = 0;
    for (size_t i = start; i <= end; i++)
    {
        dest[dest_index++] = source[i];
    }
}