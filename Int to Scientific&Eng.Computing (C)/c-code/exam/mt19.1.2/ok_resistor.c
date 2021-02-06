#include <stdio.h>

double calc_res_series(int size);
double calc_res_par(int size);

int main(int argc, char const *argv[])
{
    double result;
    char type_of_res;
    int num_of_res;
    char answer = 'N';
    char c;
    
    while('X' != answer)
    {
        printf("Enter the type of resistor\n");
        //fflush(stdin);
        scanf("%c", &type_of_res);
        printf("Enter the num of resistors\n");
        scanf("%d", &num_of_res);
        while ((c = getchar()) != '\n' && c != EOF);            //!!!!!!!!
        if (type_of_res == 'P')
        {
            result = calc_res_par(num_of_res);
        }
        else if (type_of_res == 'S')
        {
            result = calc_res_series(num_of_res);
        }
        printf("Result:\n%.2lf\nPress X for exit: ", result);
        //fflush(stdin);                                      // fflush not suggested for this buffer problem
        scanf("%c",&answer);
    }

    return 0;
}

double calc_res_par(int size) {
    double result = 0;
    int resistors[size];
    char c;
    for(size_t i = 0; i < size; ++i) {
        printf("Enter value %zu: ", (i + 1));     // %zu for type_z arguments which is i here !!!!!!!!
        scanf("%d",&resistors[i]);
        //fflush(stdin);                                //not suggested
    }
    for(size_t i = 0; i < size; ++i) {
        result += (1.0 / resistors[i]);
    }
    while ((c = getchar()) != '\n' && c != EOF);            //this is the way to go
    return 1.0 / result;
}
double calc_res_series(int size) {
    double result = 0;
    int resistors[size];
    char c;
    for(size_t i = 0; i < size; ++i) {
        printf("Enter value %zu: ", (i + 1));
        scanf("%d",&resistors[i]);
        //fflush(stdin);                                //not suggested
        result += resistors[i];
    }
    while ((c = getchar()) != '\n' && c != EOF);        //this is the way to go
    return result;
}