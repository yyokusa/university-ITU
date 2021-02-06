#include <iostream>
using namespace std;
#define ARRAY_SIZE 8

struct node {
    char value;
    node* prev;
};
struct stack {
    node* top = NULL;
    int size;
    void push(node*);
    node* pop();
    bool isempty();
};

bool check_valid_parantheses(char* ps, int ps_len) {
    stack new_stack; // empty new_stack
    char lefts[3] = {'(', '{', '['};
    char rights[3] = {')', '}', ']'};
    for(int i = 0; i < ps_len ; i++) {
        char curr = ps[i];
        if (curr == '(' || curr == '{' || curr == '[') { // if curr is a left_symbol, push onto stack
            node* new_node = new node;
            new_node->value = curr;
            new_stack.push(new_node);
        }
        else { // if curr is right_symbol
            if (stack.isempty()) {cout << "left symbol is missing" << endl ; return false;}
            else { // pop an s symbol from the stack
                node* popped_node = new_stack.pop();
                char s = popped_node->value;
                switch (s)
                {
                case '(':
                    if (curr != ')') {cout << "Ordering not appropriate" << endl; return false;}
                    break;
                case '{':
                    if (curr != '}') {cout << "Ordering not appropriate" << endl; return false;}
                    break;
                case '[':
                    if (curr != ']') {cout << "Ordering not appropriate" << endl; return false;}
                    break;
                default: // array and stack only has specified parantheses
                    return false;
                }
                delete popped_node;
            }
        }
    }
    if (!(stack.isempty())) {cout << "missing right symbol" << endl; return false;}
    return true;
}

int main() {
    char a1[] = {'[',']', '{', '(', ')', '}', '[', ']'};
    char a2[] = {'[',']', '{', '(', '}', '}', '[', ']'};
    bool result = false;
    result = check_valid_parantheses(a1, ARRAY_SIZE);
    cout << result << endl;
    result = check_valid_parantheses(a2, ARRAY_SIZE);
    cout << result << endl;
    return 0;
    }

bool stack::isempty() {
    return size == 0;
}
void stack::push(node* new_node) {
    new_node->prev = top;
    this->top = new_node;
}
node* stack::pop() {
    if (top == NULL) {
        cout << "No more elements " << endl;
        return NULL;
    }
    node* temp = this->top;
    this->top = this->top->prev;
    return temp;
}