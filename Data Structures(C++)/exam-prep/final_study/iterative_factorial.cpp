#include <iostream>
using namespace std;

int factorial(int number);
    
int main() {
    cout << factorial(0) << endl;
    cout << factorial(1) << endl;
    cout << factorial(3) << endl;
    cout << factorial(4) << endl;
    // int result;
    try {
        factorial(-14);
        // throw 1222;
        // throw 7.23;
    } catch (const char* msg) {
        cout << "String exception, " << msg << endl;
    } catch (int n) {
        cout << "Integer exception, " << n << endl;
    } catch (...) {
        cout << "Default exception." << endl;
    }
    return 0;
}

int factorial(int number) {
    if (number < 0) {throw "Can not except negative numbers.";}
    if (number <= 1) {return 1;}
    int result = 1;
    for (size_t i = 2; i <= number; i++)
    {
        result *= i;
    }
    return result;
}
