#include <iostream>
#include "bstree.h"

using namespace std;

void BSTree::initialize(){
    root = NULL;
}

void BSTNode::initialize(int number){
    data = number;
    left = NULL;
    right = NULL;
}

void BSTree::add(int number) {
    if(root==NULL){
        root = new BSTNode;
        root->initialize(number);
    }
    else {        
        BSTNode* newnode = new BSTNode;
        newnode->initialize(number);
        root->add(newnode);
    }
}

void BSTNode::add(BSTNode* newnode){
    if(newnode->data > data){
        if(right)
            right->add(newnode);
        else
            right = newnode;
        
    }
    else if(newnode->data < data){
        if(left)
            left->add(newnode);
        else
            left = newnode;
    }
}

BSTNode* BSTree::remove(int number){
    BSTNode* ptr = search(number);
    if(!ptr)
        return NULL;
    BSTNode* ptr_par = search_parent(number);
    
    if(!ptr_par){   // removing root
        if(!ptr->left && !ptr->right){  // if root has no child
            root=NULL;
            return ptr;
        }
        if(ptr->left){                // root has a left child
            root=ptr->left;           // make left child new root
            if(ptr->right)            // if right child did exist for the old root,
                root->add(ptr->right);// add old right child as new right child(right tree) to the new root
        }
        else if(ptr->right) root=ptr->right; // root doesn't have a left child, only has a right child, make right child as root
    }
    else{ // to be removed node is not the root
        if(ptr_par->left==ptr) // node in parent's left
            ptr_par->left=NULL;
        else ptr_par->right=NULL; // node in parent's right
        if(ptr->left) root->add(ptr->left); // why not call add on parent instead of root?
        if(ptr->right) root->add(ptr->right);
    }
    return ptr;
}

BSTNode* BSTree::search(int number){
    BSTNode *ptr=root;
    while(ptr!=NULL){
        if(number>ptr->data)
            ptr = ptr->right;
        else if(number<ptr->data)
            ptr = ptr->left;
        else return ptr;
    }
    return ptr;
}

BSTNode* BSTree::search_parent(int number){
    BSTNode *ptr=root;
    if(ptr->data == number)
        return NULL;
    while(ptr!=NULL){
        if((ptr->right && ptr->right->data == number) || 
           (ptr->left && ptr->left->data == number))
           return ptr;
        if(number>ptr->data)
            ptr = ptr->right;
        else if(number<ptr->data)
            ptr = ptr->left;
    }
    return ptr;
}

void inorder(BSTNode *nptr) {
  if (nptr) {
    inorder(nptr->left);
	cout << nptr->data << " ";
    inorder(nptr->right);
  }
}

void BSTree::print_tree(){
  inorder(root);
  cout << endl;
}

void BSTree::destroy(){
    root->destroy();
    delete root;
    root = NULL;
}

void BSTNode::destroy(){
    if(left) {
        left->destroy();
        delete left;
    }
    if(right) {
        right->destroy();
        delete right; 
    } 
}

