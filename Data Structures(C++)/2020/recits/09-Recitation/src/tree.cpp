#include <iostream>
#include "tree.h"
#include "stack.h"

using namespace std;

void build_trivial_tree(Tree& aTree){

    aTree.root = new Node;
    aTree.root->data = 1;

    aTree.root->left = new Node;
    aTree.root->left->data = 2;
    
    aTree.root->right = new Node;
    aTree.root->right->data = 3;    
    
    aTree.root->left->left = new Node;
    aTree.root->left->left->data = 4;
    aTree.root->left->left->left = NULL;
    aTree.root->left->left->right = NULL;
    
    aTree.root->left->right = new Node;
    aTree.root->left->right->data = 5;
    aTree.root->left->right->left = NULL;
    aTree.root->left->right->right = NULL;

    aTree.root->right->left = new Node;
    aTree.root->right->left->data = 6;
    aTree.root->right->left->left = NULL;
    aTree.root->right->left->right = NULL;
    
    aTree.root->right->right = new Node;
    aTree.root->right->right->data = 7;
    aTree.root->right->right->left = NULL;
    aTree.root->right->right->right = NULL;

}

void destroy_trivial_tree(Tree& aTree){

    delete aTree.root->left->left;
    delete aTree.root->left->right;
    delete aTree.root->right->left;
    delete aTree.root->right->right;

    delete aTree.root->left;    
    delete aTree.root->right;

    delete aTree.root;
}

void preorder(Node *nptr) {
	 if (nptr) {
	   cout << nptr->data << " ";
	   preorder(nptr->left);
	   preorder(nptr->right);
	 }
}

void inorder(Node *nptr) {
  if (nptr) {
    inorder(nptr->left);
	  cout << nptr->data << " ";
    inorder(nptr->right);
  }
}

void postorder(Node *nptr) {
  if (nptr) {
    postorder(nptr->left);
    postorder(nptr->right);
    cout << nptr->data << " ";
  }
}

void iter_inorder(Node *nptr) {
  Node* current=nptr;
  bool flag = true;
  Stack<Node*> s;
  s.create();
  while (flag) {
	  while (current != NULL) {
		s.push(current);
		current = current->left;
	  }
    if ( !s.isempty() ) {
	 current = s.pop();
	 cout << current->data << " ";
	 current = current->right;
    }
    else
	 flag = false;
  }
}

