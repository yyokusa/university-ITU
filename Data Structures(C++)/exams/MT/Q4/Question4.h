/* @Author
Student Name:YASIN ABDULKADIR YOKUS
Student ID :150190739
Date:09/12/2020
*/


void question4();
struct mnode{
public:
    int data;// if integer root, root ptr points to root, else NULL
	mnode* next;
	mnode* root; 
};
// ascending order
struct Multilist
{
public:
    mnode* headptr;
    void create();
    void add(int number);
    void printroots(mnode *start);
    mnode* returnadressof(int value);
};