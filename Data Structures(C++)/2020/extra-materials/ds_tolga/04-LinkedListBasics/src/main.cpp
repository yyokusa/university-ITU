#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

struct LinkedList
{
    Node *head;
};

void add_to_list(LinkedList &, int);
void print_list(LinkedList &);
void remove_list(LinkedList &);
double stdev(LinkedList &, double, int);

int main()
{
    LinkedList a_list;
    a_list.head = new Node;
    a_list.head->data = -1;
    a_list.head->next = a_list.head;

    int cur_grade = 0;
    int count = 0;
    double acc = 0;

    cout << "Please input grades. Input -1 to stop" << endl;

    while (true)
    {
        cout << endl
             << "Next grade ";
        cin >> cur_grade;

        if (cur_grade == -1)
            break;

        acc += cur_grade;
        add_to_list(a_list, cur_grade);
        count++;
    }

    print_list(a_list);
    double average = 0;
    if (count != 0)
        average = acc / count;

    cout << "Average grade score is: " << average << endl;
    cout << "Stdev of grades is: " << stdev(a_list, average, count) << endl;

    system("pause");
    remove_list(a_list);
    return EXIT_SUCCESS;
}

void remove_list(LinkedList &list)
{
    Node *ptr = list.head->next;
    Node *todelete;

    while (ptr != list.head)
    {
        todelete = ptr;
        ptr = ptr->next;
        delete todelete;
    }
    delete list.head;
}

void print_list(LinkedList &list)
{
    Node *ptr = list.head->next;

    cout << "||->";
    while (ptr != list.head)
    {
        cout << ptr->data << "->";
        ptr = ptr->next;
    }
    cout << " |" << endl;
}

void add_to_list(LinkedList &list, int grade)
{
    Node *toadd = new Node;
    toadd->data = grade;
    toadd->next = NULL;

    Node *ptr = list.head->next;
    while (ptr->next != list.head && ptr->next->data < toadd->data)
        ptr = ptr->next;

    if (ptr->data > toadd->data)
        ptr = list.head;

    toadd->next = ptr->next;
    ptr->next = toadd;
}

double stdev(LinkedList &list, double average, int grade_count)
{

    if (grade_count == 0)
        return 0;

    double stdev = 0;

    Node *ptr = list.head->next;

    while (ptr != list.head)
    {
        stdev += pow(ptr->data - average, 2);
        ptr = ptr->next;
    }

    return sqrt(stdev / grade_count);
}