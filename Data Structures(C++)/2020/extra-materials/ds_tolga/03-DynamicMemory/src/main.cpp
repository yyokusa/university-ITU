#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Expression
{
        struct Expression *ope1 = NULL;
        char op1;
        char oprt;
        char op2;
        struct Expression *ope2 = NULL;
        void print_expr();
};

void foo(int **);
void swap1(int, int);
void swap2(int &, int &);
void swap3(int *, int *);
int strlen1(const char *);
int strlen2(const char *);

int main(){

        /*
    int a = 1, b = 5;
    cout << "Before--> a:" << a << " b:" << b << endl;
    swap1(a, b);
    cout << "Swap1--> a:" << a << " b:" << b << endl;
    swap2(a, b);
    cout << "Swap2--> a:" << a << " b:" << b << endl;
    swap3(&a, &b);
    cout << "Swap3--> a:" << a << " b:" << b << endl;
*/
        /*
    int x = 5;
    int* ptr = &x;
    int** ptptr = &ptr; 

    cout << *ptr << endl;

    foo(ptptr);

    cout << *ptr << endl;
    *ptr=15;
  
    cout << *ptr << endl;
    foo(ptptr);

*/
        /*
    char a[10] = "array";
    int k;
    char *ptr = a;
    cout << "strlen1: " << strlen1("hello world") <<endl;
    cout << "strlen1: " << strlen1(a) <<endl;
    cout << "strlen1: " << strlen1(ptr) <<endl;

    cout << "strlen2: " << strlen2("hello world") <<endl;
    cout << "strlen2: " << strlen2(a) <<endl;
    cout << "strlen2: " << strlen2(ptr) <<endl;
*/
        /*
struct Expression expr1, expr2, expr3, expr4;

expr1.op1 = '5';
expr1.oprt = '+';
expr1.op2 = '2';
expr1.print_expr();
cout << endl;

expr2.op1 = '3';
expr2.oprt = '/';
expr2.op2 = '2';
expr2.print_expr();
cout << endl;

expr3.ope1 = &expr1;
expr3.oprt = '*';
expr3.ope2 = &expr2;
expr3.print_expr();
cout << endl;

expr4.ope1 = &expr3;
expr4.oprt = '-';
expr4.ope2 = &expr3;
expr4.print_expr();
cout << endl;
*/

        getchar();
        return EXIT_SUCCESS; //-->stdlib.h

}

void swap1(int x, int y){
        int temp;
        temp = x;
        x = y;
        y = temp;
}

void swap2(int &x, int &y){
        int temp;
        temp = x;
	     x = y;
        y = temp;
}

void swap3(int *xptr, int *yptr){
        int temp;
        temp = *xptr;
	     *xptr = *yptr;
        *yptr = temp;
}

void foo(int **p)
{
        int y = 10;
        cout << **p << endl;
        (*p) = &y;
}

int strlen1(const char *s){
        int n = 0;
        for (n = 0; *s != '\0'; s++)
             n++;
        return n;
}

int strlen2(const char *s){
        int n = 0;
        while (*s){
             s++;
             n++;
       }
        return n;
}

void Expression::print_expr()
{
        if (!ope1)
                cout << op1;
        else
        {
                cout << "(";
                ope1->print_expr();
                cout << ")";
        }
        cout << oprt;

        if (!ope2)
                cout << op2;
        else
        {
                cout << "(";
                ope2->print_expr();
                cout << ")";
        }
}

