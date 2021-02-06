#include <stdio.h> // fgets
#include <stdlib.h> // atoi
#include <string.h> // strlen, strcpy

typedef struct{
    int up;
    int down;
}Fraction;

void getFraction(Fraction* fraction) {
    printf("Enter the elements of fraction in order of up and down: ");
    scanf("%d %d", &(fraction->up), &(fraction->down));
}
void printFraction(Fraction* fraction) {
    printf("Printing fraction ");
    printf("up: %d\n", fraction->up);
    printf("down: %d\n", fraction->down);
}
void multiplyFraction(Fraction* resFraction, Fraction* fraction1, Fraction* fraction2) {
    printf("Multiplying fractions... \n");
    resFraction->up = (fraction1->up)*(fraction2->up);
    resFraction->down = (fraction1->down)*(fraction2->down);
}
int main() {
    Fraction fraction1;
    Fraction fraction2; 
    Fraction resFraction; 
    
    getFraction(&fraction1);
    getFraction(&fraction2);
    multiplyFraction(&resFraction, &fraction1, &fraction2);
    printFraction(&resFraction);
    
    // Fraction* fraction1 = (Fraction*)malloc(sizeof(Fraction));
    // Fraction* fraction2 = (Fraction*)malloc(sizeof(Fraction));
    // Fraction* resFraction = (Fraction*)malloc(sizeof(Fraction));
    
    // getFraction(fraction1);
    // getFraction(fraction2);
    // multiplyFraction(resFraction, fraction1, fraction2);
    // printFraction(resFraction);
    
    // free(fraction1);
    // free(fraction2);
    // free(resFraction);
    return 0;
}

// void incrementClock();
// void showClock();


// typedef struct{
//     int hours;
//     int minutes;
//     int seconds;
// }Clock;

// void incrementClock(Clock* clock) {
//     ++(clock->seconds);
//     if(clock->seconds == 60) {
//         clock->seconds = 0;
//         ++(clock-> minutes);
//         if(clock->minutes == 60) {
//             clock->minutes = 0 ;
//             ++(clock->hours);
//             if(clock->hours == 24) {
//                 clock->hours = 0 ;
//             }
//         }
//     }
// }

// void showClock(Clock* clock) {
//     printf("%02d:%02d:%02d\n", clock->hours, clock->minutes, clock->seconds);
// }

// int main() {
//     Clock clock = {3,8,3};
//     int i = 0;
//     while(i < 4) {
//         incrementClock(&clock);
//             showClock(&clock);
//         // if (i%1000 == 0) {
//         // }
//         ++i;
//     }
//     return 0;
// }

// /* 
// ** my itoa
// */
// // base 10
// void  my_itoa ( int value, char* str){
//     char* ptr = NULL;
//     int num = 0;
//     if (value < 0) {
//         *ptr++ = '-';
//     } 
//     do {
//         num = (value % 10) + '0';               //!!!!!!!!!!!!!!!ASCII Chart!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//         *ptr++ = num;
//     }while(value /= 10);
//     *ptr = '\0';

//     //return str;
// }
// int main() {
//     char str[10];
//     my_itoa(1923, str);
//     printf("sentence is: %s", str);
    
//     return 0;
// }