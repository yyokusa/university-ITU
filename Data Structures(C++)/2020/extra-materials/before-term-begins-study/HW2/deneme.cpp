#include <iostream>

using namespace std;

int main() {
    char name[25] = "akali12@";
    char name2[25] = "akali";
    // char* ptr = name;
    // int len = 0;
    // while (*ptr != '\0') {
    //     len++;
    //     cout << len << endl;
    //     cout << *ptr << endl;
    //     ptr++;
    // }
    // cout << name << endl;
    // cout << len << endl;
    
    cout << strcmp(name, name2) << endl;


    return 0;   
}


/*
    TODOS
    * Implement UTF - 8 (Turkish Characters)
    * Implement MIDDLE NAME
    * Implement case insensitivity
*/