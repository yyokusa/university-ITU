#include <iostream>
#include <string>
using namespace std;

//                  ABC
//          |             |                   |
//        A - A          A - B              A - C
//       ABC              BAC                CBA
//     |      |          |         |         |     |
//   B - B    B - C     A - A   C - A      B - B     B - A
//  ABC        ACB       BAC      BCA       CBA       CAB

void permutation(string&, int, int);
    
int main() {
    string str = "ABC";
    int left = 0;
    int right = str.length() - 1;
    permutation(str, left, right);
    return 0;
}

void permutation(string& str, int left, int right) {
    if (left == right) {
        cout << str << endl;
        return;
    }
    for (size_t i = left; i <= right; i++)
    {
        swap(str[left], str[i]);
        permutation(str, left + 1, right);
        swap(str[left], str[i]);
    }
}