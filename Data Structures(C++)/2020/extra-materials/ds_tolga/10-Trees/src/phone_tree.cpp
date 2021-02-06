#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <iostream>
#include "phone_tree.h"

using namespace std;

void Phone_Tree::create()
{
    root = NULL;
}

bool Phone_Tree::search(const char *target)
{
    Phone_Node *traverse;
	traverse = root;
	if (target[0] == '*'){
     	print_tree();
		return true;
	}
    else { // single record search
	    while (traverse) {
            if (strcmp(target, traverse->phone_record->name) < 0)
	            traverse = traverse->left;
	        else if (strcmp(target,traverse->phone_record->name) > 0)
		        traverse = traverse->right;
	        else { // if names are equal, record found
    	        cout << traverse->phone_record->name << " " << traverse->phone_record->phonenum << endl;
		        return true;
	        }
	    }
	}
	return false;
}


void remove_node(Phone_Node** ptr_to_remove){
    Phone_Node *removed, *q;  
	removed = *ptr_to_remove;
	if (removed == NULL) 
		return;
	if (removed->right == NULL) 
		(*ptr_to_remove) = removed->left; 
	else if (removed->left == NULL) 
		(*ptr_to_remove) = removed->right;
	else { 
		for (q = removed->right; q->left; q = q->left); 
		q->left = removed->left; 
		(*ptr_to_remove) = removed->right;
	}
	delete removed;
}

void Phone_Tree::remove(const char* name)
{
   Phone_Node *traverse, *parent;
   traverse = root;
   bool found = false;
   char direction = 'k';
   while (traverse && !found) {
      if (strcmp(name, traverse->phone_record->name) < 0) {
         parent = traverse;
         direction = 'l';
         traverse = traverse->left;
      }
      else if (strcmp(name, traverse->phone_record->name) > 0) {
         parent = traverse;
         direction = 'r';
         traverse = traverse->right;
      }
      else // found record to remove
         found = true;
   }
   if (found) {
      if (direction == 'l')
         remove_node(&(parent->left));
      else if(direction == 'r')
         remove_node(&(parent->right));
      else remove_node(&root);
   }
   else
      cout << "Could not find record to remove.\n";
}

bool Phone_Tree::insert(Phone_Record& newrecord)
{
    Phone_Node *traverse;
    traverse = root;
    bool added = false;
    if (root == NULL){ 
        root = new Phone_Node;
        root->build_node(newrecord);
        return true;
	}
    while ((traverse != NULL) && (!added)){
	    if (strcmp(newrecord.name, traverse->phone_record->name) < 0) {
	        if (traverse->left != NULL)
	            traverse = traverse->left;
            else {
                traverse->left = new Phone_Node;
	    	    traverse->left->build_node(newrecord);
		        added = true;
            }
	    }
	    else if (strcmp(newrecord.name, traverse->phone_record->name) > 0) {
	        if (traverse->right != NULL)
	            traverse = traverse->right;
	        else{
		        traverse->right = new Phone_Node;
                traverse->right->build_node(newrecord);
		        added = true;
	        }
	    }
	    else{
	        cout << "Record already present, no changes made!!\n";
            return false;
        }
    }
    return true;
}

void Phone_Tree::update(const char* name,Phone_Record& newrecord)
{
    remove(name);
    insert(newrecord);
}

void remove_subtree(Phone_Node* p){
    if (p) {
        if (p->left != NULL) {
            remove_subtree(p->left);
            p->left = NULL;
        }
        if (p->right != NULL) {
            remove_subtree(p->right);
            p->right = NULL;
        }
        delete p;
    }
}

void Phone_Tree::clear(){
    remove_subtree(root);
    root=NULL;
}

void traverse_inorder(Phone_Node *p) {
   if (p){
      traverse_inorder(p->left);
      cout << p->phone_record->name << " " << p->phone_record->phonenum << endl;
      traverse_inorder(p->right);
   }
}

void Phone_Tree::print_tree(){
    traverse_inorder(root);
}
