#include <iostream>
#include <fstream>
#include <string>
#include <string.h>				   
#include <queue>
using namespace std;

//Assuming that you are given two binary search trees, whose data structures and creation methods are provided below, you are asked to 
//write a recursive mergeBST function which will take two binary search trees as arguments, traverse them with a traversal method up to your choice and return a new binary tree (not necessarily a BST) which will be the sum of the input
//trees' elements occuring at the same tree position (i.e., whose nodes are  superimposed sums of the nodes of the two trees). The original trees should  stay the same; you are not allowed to change them or use their nodes
//directly in the construction of the new tree. In other words, the resulting binary tree should be constructed from scratch with its
//own nodes. The signature of the method and the main function are provided. 
//You are NOT allowed to change the main function. Please only fill in
//the body part of the mergeBST method. Writing extra methods is not allowed.
//An example is given below.  The recursive method should be as short as possible (avoid any unnecessary lines) and the created shape should be very similar to the initial trees. 
// A sample input file (input.txt with an empty line between the two trees' elements) and a sample output message are provided. Your code will be tested with similar inputs.



struct BTnode{
	int data;
	BTnode *left;
	BTnode *right;
};
struct BT{
	BTnode *root;
	BTnode *sentinel;//do not use this pointer
	void add(int);
	void create();
};
void BT::create(){
	root = NULL;
	sentinel = new BTnode;
}
//level order addition
void BT::add(int indata){
	BTnode *traverse, *newnode;
	traverse = root;

	bool added = false;
	newnode = new BTnode;
	newnode->data = indata;
	newnode->left = NULL;
	newnode->right = NULL;
	if (root == NULL){
		root = newnode;
		return;
	}
	while ((traverse != NULL) && (!added)){
		if (indata < traverse->data) {
			if (traverse->left != NULL)
				traverse = traverse->left;
			else {
				traverse->left = newnode;
				added = true;
			}
		}
		else if (indata > traverse->data) {
			if (traverse->right != NULL)
				traverse = traverse->right;
			else {
				traverse->right = newnode;
				added = true;
			}
		}
	}
}
/* Print nodes at a given level */
void printGivenLevel(BTnode* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		cout << root->data << " ";
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}

/* Compute the "height" of a tree -- the number of
nodes along the longest path from the root node
down to the farthest leaf node.*/
int height(BTnode* node)
{
	if (node == NULL)
		return 0;
	else
	{
		/* compute the height of each subtree */
		int lheight = height(node->left);
		int rheight = height(node->right);

		/* use the larger one */
		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}
/* Function to print level order traversal a tree*/
void print(BT t){
	int h = height(t.root);
	int i;
	for (i = 1; i <= h; i++)
		printGivenLevel(t.root, i);
}

BTnode* mergeBST(BTnode *bt1, BTnode *bt2){
	BTnode* new_node = new BTnode;
	new_node->left = NULL;
	new_node->right = NULL;
	if (bt1 != NULL && bt2 != NULL) {
		new_node->data = bt1->data + bt2->data;
		new_node->left = mergeBST(bt1->left, bt2->left);
		new_node->right = mergeBST(bt1->right, bt2->right);
	} else if (bt1 != NULL) {
		new_node->data = bt1->data;
		new_node->left = mergeBST(bt1->left, NULL);
		new_node->right = mergeBST(bt1->right, NULL);
	} else if (bt2 != NULL) {
		new_node->data = bt2->data;
		new_node->left = mergeBST(NULL, bt2->left);
		new_node->right = mergeBST(NULL, bt2->right);
	} else {
		delete new_node;
		return NULL;
	}
	return new_node;
}
int main(int argc, char* argv[]){
	BT mybt1, mybt2, mybt3;
	mybt1.create(); mybt2.create(); mybt3.create();
	string line;
	string filepath="inputQ1.txt";
	if (argc>1)
	{
	filepath=argv[1];
	}
	ifstream myfile(filepath);
	if (myfile.is_open())
	{
		while (getline(myfile, line) && line!="" && line!="\r")
		{
			mybt1.add(stoi(line));
		}
		while (getline(myfile, line) && line!="" && line!="\r")
		{
			mybt2.add(stoi(line));
		}
		myfile.close();
	}
	else cout << "Unable to open file";


	mybt3.root = mergeBST(mybt1.root, mybt2.root);

	print(mybt1);
	cout << endl << "####" << endl;
	print(mybt2);
	cout << endl << "####" << endl;
	print(mybt3);
	cout << endl << "####" << endl;
/* The output should be as follows for the input.txt
3 1 5 4 7
####
5 2 7 1 3 8 0 4
####
8 3 12 1 3 4 15 0 4
####

*/
	getchar();
  	return 0;	   
}
