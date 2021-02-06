#include <iostream>
using namespace std;
struct Node {
    int row;
    int col;
    int value;
    Node* next;
};

struct LinkedList {
    int row_m;
    int col_m;
    Node* head;
    void create();
    void add(int, int, int); // row, col, value
    void print(); // print the matrix
    int deleteList();
};

void LinkedList::deleteList() {
    // int i = 0;
    Node* ptr = head;
    Node* temp = head;
    while(ptr) {
        temp = ptr;
        ptr = ptr->next;
        delete temp;
        // i++;
    }
    // return i;
}



void LinkedList::create() {
    head = NULL;
    cout << "Please enter the row and column numbers of sparse matrix: " << endl;
    cin >> row_m;
    cin >> col_m;
}

void LinkedList::print() {
    Node* ptr = head;
    int traverse_row = 0;
    int traverse_col = 0;
    while(traverse_row < row_m) {
        int row_to_print_value = ptr->row;
        int col_to_print_value = ptr->col;
        while (traverse_col < col_m) // 0 to col_m - 1 ==> col_m 0s max
        {
            if (traverse_row == row_to_print_value && traverse_col == col_to_print_value) {
                cout << ptr->value << " ";
                traverse_col++;
                continue;
            }
            cout << "0 ";
            traverse_col++;
        }
        traverse_col = 0;
        cout << endl;
        traverse_row++;
        ptr = ptr->next;
    }
}

void LinkedList::add(int row, int col, int value) {
    Node* new_node = new Node;
    new_node->row = row;
    new_node->col = col;
    new_node->value = value;
    new_node->next = NULL;
    Node* ptr = head;
    Node* prev = head;
    if (head == NULL) { // insert first node as head
        head = new_node;
        return;
    }
    if (row < ptr->row) {
        new_node->next = head;
        head = new_node;
        return;
    }
    //   TRUE     &&      FALSE          &&   (TRUE && TRUE)
    while(ptr != NULL && ptr->row < row) { // only time this cond turns out true is when ptr->row equals to row
        prev = ptr;
        ptr = ptr->next;
    }
    if (ptr == NULL) { // ptr is NULL, prev is last node
        prev->next = new_node;
    } else if (ptr->row == row && ptr->col > col) {
        prev->next = new_node;
        new_node->next = ptr;
    }
    else if (ptr->row > row) { // row is smaller than ptr->row, insert before the ptr
        prev->next = new_node;
        new_node->next = ptr;       
    }
}


LinkedList ll;
int main() {
    ll.create();
    bool flag = true;
    while(flag) {
        int row = 0;
        int col = 0;
        int value = 0;
        
        cout << "Please enter the row, column and value for sparse matrix entry: " << endl;
        cin >> row;
        cin >> col;
        cin >> value;
        ll.add(row, col, value);

        cout << "Will you enter more entries? \"Y\" for yes, \"N\" for no" << endl;
        char answer;
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            continue;
        } else if (answer == 'N' || answer == 'n'){
            flag = false;
        }
    }
    ll.print();
    // cout << ll.deleteList() << endl;
    ll.deleteList();
    return 0;
}