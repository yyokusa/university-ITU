#include <iostream>
#include <cstdio>
#include <string>
#include <typeinfo>

using namespace std;

#define ARRAY_SIZE 4

struct Student{
    string name;
    int no;
};
// void f(int** p, int* k);
void print(int* ptr);

struct node{
       char firstname[20];
       char lastname[20];
       node *next;
};
node* add(char *firstname, char *lastname){
    node *newnode = new node;
    strcpy(((*newnode).firstname), firstname);
    strcpy(newnode->lastname, lastname);
    return newnode;
};

int findDiffIndex(const char* str1, const char* str2) {
    int index = 0;
    char a;
    char b;
    while ((a = str1[index]) != '\0' && (b = str2[index]) != '\0') {
        if (a == b) {
            index++;
            continue;
        } else {
            break;
        }
    }
    return index;
}
int findDelimIndex(const char* str1, char delim) {
    int index = 0;
    char a;
    while ((a = str1[index]) != '\0') {
        if (a == delim) {
            return index;
        }
        index++;
    }
    return -1;
}

void subString(const char* str, const int start, const int end, char* res) {
    int index = 0;
    while (index < end && str[index] != '\0') {
        res[index] = str[index];
        index++;
    }
    res[index] = '\0';
}



int main(int argc, char const *argv[])
{
    /* char a[12] = "akali";
    char b[12] = "ak"; */
    /* cout << strcmp(b, a) << endl;
    cout << (int)'\0' << endl; */
   
    // cout << findDiffIndex(a, b) << endl;

    // char s[30] = "yok@itu.edu.tr";
    // char token[20] = s.substr(0, 3)); // token is "scott"
    // cout << findDelimIndex(s, delimiter) << endl;
    // cout << token << endl;

    char str1[30] = "yokus@edu.tr";
    char str2[30] = "yokusk@edu.tr";
    char str3[20] = "yokuskadir";
    char str4[20] = "yokusabdul";
    cout << strcmp(str1, str3) << endl;
    cout << strcmp(str1, str4) << endl;
    cout << strcmp(str2, str4) << endl;
    // cout << strcmp(str1, str2) << endl;
    
    

    return 0;
    /* int p[ARRAY_SIZE] = {1,2,3,4};
    int k[ARRAY_SIZE] = {99,100,101,102};
    int* l = p;
    f(&l, k);
    
    print(p);
    cout << endl;
    print(k); */
    /* int* darray;
    darray = new int[100];
    delete [] darray; */
  /*   Student student1;
    student1.name = "yasin";
    student1.no = 100;
    Student student2 = student1;
    cout << student2.name << endl;
    cout << student2.no; */
    
    /* node Node;
    char a[] = "ahmet";
    char b[] = "cetin";
    node* ptr = add(a, b);
    Node = *ptr;
    cout << Node.firstname;
    cout << Node.lastname;
    delete ptr */


    /* char a[10] = "abc";
    cout << strlen(a) << endl; */

    /* 
    FILE* file = NULL;
    if ((file = fopen("foundWordsInfo.txt", "r")) != NULL) {
        int rowStart = 0;
        int colStart = 0;
        int rowEnd = 0;
        int colEnd = 0;
        char r1[25];
        char r2[25];
        int scanned = 0;
        scanned = fscanf(file, "%s\t%s\t[%d][%d] - [%d][%d]\n", r1, r2, &rowStart, &colStart, &rowEnd, &colEnd);
        
        cout << scanned << endl;
        while ((scanned = fscanf(file, "%d%d%d%d", &rowStart, &colStart, &rowEnd, &colEnd)) )
        {
            cout << rowStart << colStart << rowEnd << colEnd << endl;
            cout << scanned << endl;
        }
        fclose(file);
    }
    */


   // cout << (int)'İ' << endl; // character too large for enclosing character literal type

/*     char a[56];
    cout << strcat(a, "akaaaa") << endl;
 */
}

/* void f(int* p, int* k){
    p = k;
    *p = 19;
    *++p = 20;
} */

/* void f(int** p, int* k){
    *p = k;
    **p = 19;
    *++(*p) = 20;
} */

void print(int* ptr) {
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        cout << ptr[i] << endl;
    }
}




/* 1 KOVALENT
2 VANDERVALS
3 IYONIK
4 HIDROJEN
5 DIPOLDIPOL
6 ELEMENT
7 ATOM
8 MOLEKUL
9 METAL */