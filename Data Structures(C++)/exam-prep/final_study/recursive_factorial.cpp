#include <iostream>
using namespace std;

int factorial(int number);
    
int main() {
    cout << factorial(0) << endl;
    cout << factorial(1) << endl;
    cout << factorial(3) << endl;
    cout << factorial(4) << endl;
    return 0;
}

int factorial(int number) {
    if (number <= 1) {return 1;}
    return number * factorial(number - 1);
}
