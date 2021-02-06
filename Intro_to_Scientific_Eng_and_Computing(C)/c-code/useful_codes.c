// array equality
bool equals(int a[], int a_size, int b[], int b_size)
{
	if (a_size == b_size)
	{
		//proceed;
		for (int i = 0; i < a_size; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
//generate random array
void generate_random_array(int* nums, int size)
{
    srand(time(0));
    for (size_t i = 0; i < size; i++)
    {
        int number = rand() % 100;
        nums[i] = number;
    }
}
//print array
void print_array(int* nums, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        fprintf(stdout, "%d ", nums[i]);
    }
    fprintf(stdout, "\n");
}


double calculate_cumulative_average(int nums[], int size)
{
    double total = 0;
    for (size_t i = 0; i < size; i++)
    {
        total += nums[i];
    }
    return total / size;
}

double calculate_moving_average(int nums[], int size, int n)
{
    double total = 0;
    for (size_t i = size - n; i < size; i++)
    {
        total += nums[i];
    }
    return total / (n);
}
// for string
/*
//generate random array
void generate_random_array(char *string, int size)
{
    srand(time(0));
    for (size_t i = 0; i < size - 1; i++)
    {
        int randChar = rand() % 'A' + 24;
        string[i] = randChar;
    }
}
// print a string char by char
void print_array_cbyc(char *string, int size)
{
    // for (size_t i = 0; i < size; i++)
    // {
    //     fprintf(stdout, "%c ", string[i]);
    // }
    int i = 0;
    char c;
    while( (c = string[i++]) != '\0')
    {
        printf("%c", c);
    }
    fprintf(stdout, "\n");
}

// print a string by format specifier %s
void print_array_s(char *string, int size)
{
    fprintf(stdout, "%s\n", string);
}
*/

long double better_combination(double n, double r)
{
    long double term2 = factorial_with_x(r, 0);
    long double term3 = factorial_with_x(n - r, r);
    term3 = term2 * term3;
    long double temp = r > (n - r) ? r : (n - r);
    long double term1 = factorial_with_x(n, temp);
    long double temp2 = term2 > term3 ? term2 : term3;
    term1 = term1 * temp2;
    return term1 / (term2 * term3);
}

long double combination(double n, double r)
{
    long double term1 = factorial_with_x(n, 0);
    long double term2 = factorial_with_x(r, 0);
    long double term3 = factorial_with_x(n - r, 0);
    return term1 / (term2 * term3);
}

long double factorial_with_x(double n, double x)
{
    if (n == 0)
        return 0;
    long double res = n;

    while (--n > x)
    {
        res *= n;
    }
    return res;
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

void get_uppercase(char *sentence, int size)
{
    int i = 0;
    while (i != size)
    {
        char c = sentence[i]; 
        if (c >= 'a' && c <= 'z')
        {
            sentence[i] = c - ('a' - 'A');
        }
        ++i;
    }
    // putchar('\n');
    fputc('\n', stdout);
}

// dynamically created array
char** myargs = (char**) malloc(4 * sizeof(char*));
for (int i = 0; i<4;++i)
    myargs[i] = (char*) malloc(10 * sizeof(char));






// baykar insan-robot mülakat sorusu
#include <stdio.h>
#include <stdlib.h>

void fibonacci(int curr_num, int fib1, int fib2, int target);

int main(int argc, char **argv)
{

    int num = 0;
    printf("Enter target num: ");
    scanf("%d", &num);
    fibonacci(0, 0, 1, num);

    return 0;
}

void fibonacci(int curr_num, int fib1, int fib2, int target)
{
    if (curr_num == target)
    {
        printf("%d th fibonacci number is %d\n", curr_num, fib1);
        return;
    }
    printf("%d th fibonacci number is %d\n", curr_num, fib1);
    int new_number = fib1 + fib2;
    fib1 = fib2;
    fib2 = new_number;
    fibonacci(++curr_num, fib1, fib2, target);
}



void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void reverse_array(int *nums, int size)
{
    for (size_t i = 0; i < size / 2; i++)
    {
        swap(&nums[i], &nums[size - 1 - i]);
    }
}


/*
file op

#include <stdio.h>
#include <stdlib.h>
#define SIZE 80

int main() {
    unsigned int account;
    char name[30]; 
    double balance;
    FILE *fptr = NULL;
    
    if ((fptr = fopen("clients.txt","w")) == NULL) {
        puts("something went wrong while opening file");
        return EXIT_FAILURE;
    } else {
        puts("enter num, name and balance");
        puts("enter EOF to end input");
        printf("enter: ");
        while(fscanf(stdin, "%d%29s%lf", &account, name, &balance) == 3)
        {
            fprintf(fptr, "%d %s %.2f\n", account, name, balance);
            printf("enter: ");
        }
        fclose(fptr);
    }
    return EXIT_SUCCESS;
}

*/



int read_into_array(FILE* fptr_instructions, Instructions* instructions_arr) {
    int i = 0;
    while (fscanf(fptr_instructions, "%d %d", &instructions_arr[i].step, &instructions_arr[i].index) == 2) {
            ++i;
    }
    return i;
}


void read_into_array(FILE* alice, char** book) {
    int i = 0;
    while (fgets(book[i], CHARS, alice) != NULL) { //this func puts '\0' at the end of line itself...
        cleaning_the_text_little_bit(book[i]); // send a line and fix it book[i] is a line from the book[][] array of strings
        i++;
    }
}