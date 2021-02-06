#include <stdio.h> //putchar() getchar()
#include <string.h>
#include <ctype.h> //tolower()
#include <stdbool.h>

#define SIZE 11

void swap(int *a, int *b);
void bubble_sort(int sales[], int);
void print_array(int[], int);

int main(int argc, char const *argv[])
{
    int sales[SIZE] = {-5, 6, 4, 23, 12, 32, -4, 7, -6, 8, -5};
    printf("initial array:\n");
    print_array(sales, SIZE);
    bubble_sort(sales, SIZE);
    printf("after calling sort:\n");
    print_array(sales, SIZE);
    return 0;
}

void bubble_sort(int sales[], int size)
{
    // if you replace size - 1 items in the right order, the last one also replaced in the correct position
    for (size_t i = 0; i < size - 1; i++)
    {
        // bool are_swapped = false;
        for (size_t j = 0; j < size - i - 1; j++)
        {
            // if (sales[j] > sales[j + 1]) { swap(&sales[j], &sales[j+1]); are_swapped = true;}
            if (sales[j] > sales[j + 1]) { swap(&sales[j], &sales[j+1]);}
        }
        // if (!are_swapped) {break;}
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int arr[], int size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// _Bool found = 0;
// int pos = 0;
// int arr[] = {5,1,23,512,6,20,100,321,522};
// while (pos < 10 && !found)
// {
//     if (arr[pos] == 100)
//     {
//         found = 1;
//     } else
//     {
//         pos++;
//     }
// }
// printf("%d\n",pos);

// int ch;
// for (int i = 0; i < 10; i++)
// {
//     printf("%c ", (ch = getchar()));
// }

// while( (ch = getchar() ) != EOF) {
//     putchar(tolower(ch));
// }

//char a[6] = "hello";
// int length = strlen(a);
// printf("%d\n",length);
// if(scanf("%d\n",&length) != 1) {
//     printf("success\n");
// } else
//     printf("fail\n");
//************************
// int ch;
// while( (ch = getchar() ) != EOF) {
//     putchar(tolower(ch));
// }
//************************
// char ch;
// while( (ch = getchar()) ){
//     putchar(ch);
// }
// char ch;
// while( scanf("%c",&ch) ){
//     printf("%c",ch);
// }
//************************
// char ch[10];
// int i = 0;
// while( i < 9 ){
//     scanf("%c",&ch[i]);
//     ++i;
// }
// i = 0;
// while( ch[i] != '\0' ){
//     printf("%c",ch[i]);
//     ++i;
// }

//************************

// A format string containing the * character followed by a letter/symbol passed to scanf() will be read but discarded from the final result. It also wont add the characters it discarded to the number of characters it read from the input. So for example:

//     include <stdio.h>
//     #include <string.h>
//     #include <stdlib.h>

//     int main(void){

//             int day;
//             int month;
//             int year;

//             puts("Enter a date");
//             scanf("%d%*c%d%*c%d",&day, &month, &year);

//             printf("Day is: %d\nMonth is: %d\nYear is %d\n", day, month,$

//     }

// This is a common program used to demonstrate assignment-suppression. What scanf did was to read all the characters in the stream and assign only those that are integers to the variables in its argument lists.

// You should have the following as output:

//     12/4/2005
//     Day is: 12
//     Month is: 4
//     Year is 2005

//************************

// // char sentence []="Rudolph is 12 years old";
// // char str [20];
// double i;
// i = 117.2;
// // char ch;
// printf("%8.2f\n",i);
// scanf("%lf",&i);
// printf("%8.2f\n",i);
// // sscanf (sentence,"%s %*s %d",str,&i);
// // printf ("%s -> %d\n",str,i);

//********************************************

//    char ch = 'a';

//    switch (ch)
//    {
//    case 'a':
//        printf("error\n");
//        return 1;
//        break;
//    case 'b':
//        printf("general\n");
//        break;
//    case 'c':
//        printf("kenobi\n");
//        break;
//    default:
//        break;
//    }