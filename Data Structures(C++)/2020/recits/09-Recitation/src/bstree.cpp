#include <iostream>
#include "bstree.h"
#include "queue.h"

using namespace std;

void BSTree::initialize(){
    root = NULL;
}

void BSTNode::initialize(int number){
    data = number;
    left = NULL;
    right = NULL;
}

void BSTree::add(int number){
    if(root==NULL){
        root = new BSTNode;
        root->initialize(number);
    }
    else{        
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
    
    if(!ptr_par){
        if(!ptr->left && !ptr->right){
            root=NULL;
            return ptr;
        }
        if(ptr->left){
            root=ptr->left;
            if(ptr->right)
                root->add(ptr->right);
        }
        else if(ptr->right) root=ptr->right;
    }
    else{
        if(ptr_par->left==ptr)
            ptr_par->left=NULL;
        else ptr_par->left->right=NULL;
        if(ptr->left) root->add(ptr->left);
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

void BSTree::BFS_search() {

    Queue<BSTNode*> frontier;
    frontier.create();
    if (root) {
        frontier.enqueue(root);
    }
    BSTNode *temp;
    while(!frontier.isempty())
    {
        //frontier.print_queue();
        temp = frontier.dequeue();
        cout << temp->data << " ";
        if(temp->left)
            frontier.enqueue(temp->left);
        if(temp->right)
            frontier.enqueue(temp->right);
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
    if(left) left->destroy();
    if(right) right->destroy();
    delete left;
    delete right; 
}

