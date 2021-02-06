/* @Author
Student Name:YASIN ABDULKADIR YOKUS
Student ID :150190739
Date:09/12/2020
*/


#pragma once





struct Node {
    int value;
    Node* next;
};

struct Linkedlist    {
    Node* head;
    void create();
    void clear();
    void add2beginning(int i);
};

// void Linkedlist::create() {
//     head = NULL;
// }

// void Linkedlist::clear() {
//     Node* ptr = head;
//     Node* temp = ptr;
//     while(ptr != NULL) {
//         temp = ptr;
//         ptr = ptr->next;
//         // cout << "Deleting the value " << temp->value << endl;
//         delete ptr;
//     }
// 	head = NULL;
// }

// void Linkedlist::add2beginning(int i) {
//     Node* new_node = new Node;
//     new_node->next = NULL;
//     new_node->value = i;
//     if (head == NULL) {
//         head = new_node;
//         // cout << "added the value " << new_node->value << " as head " << endl;
//     }
//     else {
//         new_node->next = head;
//         head = new_node;
//         // cout << "added the value " << new_node->value << endl;
//     }
// }

void question3();

