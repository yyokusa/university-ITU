#pragma once

struct Node {
	int data;
	Node *left;
	Node *right;
};

struct Tree {
	Node *root;
};

void build_trivial_tree(Tree&);
void destroy_trivial_tree(Tree&);
void preorder(Node *);
void inorder(Node *);
void postorder(Node*);
void iter_inorder(Node *);