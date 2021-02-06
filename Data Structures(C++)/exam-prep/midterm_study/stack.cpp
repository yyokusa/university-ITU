// stack using single linked list

#include <iostream>
using namespace std;

struct Node {
    char value;
    Node* next;
};
// Stack struct definition
struct Stack {
    Node* head;
    int elemet_count;
    void create();
    void close();
    void push(char);
    char pop();
    bool isempty();
    void print();
};

void Stack::create() {
    head = NULL;
    elemet_count = 0;
}
void Stack::close() {
    Node* ptr = head;
    Node* temp = head;
    while(ptr) {
        temp = ptr;
        ptr = ptr->next;
        delete temp;
        elemet_count--;
    }
    head = NULL;
}

char Stack::pop() {
    cout << "Popping an element " << endl;
    if (head == NULL) {return ' ';}
    char tempValue = head->value;
    Node* temp = head;
    head = head->next;
    delete temp;
    elemet_count--;
    return tempValue;
}

bool Stack::isempty() {
    return head == NULL;
}


void Stack::push(char value) {
    Node* new_node = new Node;
    new_node->value = value;
    new_node->next = head;
    head = new_node;    
    elemet_count++;
}

void Stack::print() {
    if (!(this->isempty())) {
        Node* ptr = head;
        cout << "Top\n";
        while(ptr) {
            cout << ptr->value << endl;
            ptr = ptr->next;
        }
        cout << "Bottom" << endl;
    }
    else {
        cout << "Stack is empty " << endl;
    }
}


Stack st;
int main() {
    st.create();
    st.push('A');
    cout << "Calling isempty() " << endl;
    cout << st.isempty() << endl;
    cout << "Calling pop() " << endl;
    cout << st.pop() << endl; 
    cout << "Calling isempty() again " << endl;
    cout << st.isempty() << endl;



    st.push('B');
    st.print();
    cout << "Element count is " << st.elemet_count << endl;
    st.push('C');
    st.push('D');
    st.push('E');
    st.push('F');
    st.print();
    cout << "Element count is " << st.elemet_count << endl;

    // pop
    cout << st.pop() << endl;
    cout << st.pop() << endl;
    cout << st.pop() << endl;
    // pop



    cout << "Calling close " << endl;
    st.close();
    cout << "Element count is " << st.elemet_count << endl;
    cout << "Calling isempty() again " << endl;
    cout << st.isempty() << endl;
    return 0;
}