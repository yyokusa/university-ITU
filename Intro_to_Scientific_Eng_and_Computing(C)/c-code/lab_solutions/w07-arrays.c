#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArray(int[], int size);
void printArray(int newArr[], int size);
double moving_average(int newArr[], int size, int n);
double cumm_average(int newArr[], int size);

int main() {
    int arr_size = 0;
    scanf("%d", &arr_size);
    const int size = arr_size;
    int newArr[size];

    //fill array
    fillArray(newArr, size);
    printArray(newArr, size);
    int moving_average_num = 0;
    printf("Moving avg of how many nums?\n");
    scanf("%d", &moving_average_num);

    printf("cumm avrg is: %lf", cumm_average(newArr,size));
    printf("\n");
    printf("moving avrg is: %lf", moving_average(newArr,size, moving_average_num));

    
    return 0;
}

void fillArray(int newArr[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("Enter a number: ");
        scanf("%d", &newArr[i]);
    }

    return;
}

void printArray(int newArr[], int size) {
    printf("Printing array:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d", newArr[i]);
        printf("\n");
    }

    return;
}



double cumm_average(int newArr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += newArr[i];
    }

    return (float)sum / size;
}



double moving_average(int newArr[], int size, int n) {
    int sum = 0;
    for (int i = size - n; i < size; ++i) {
        sum += newArr[i];
    }

    return (float)sum / n;
}