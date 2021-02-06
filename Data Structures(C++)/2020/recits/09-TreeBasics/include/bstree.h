#pragma once

struct BSTNode {
	int data;
	BSTNode *left;
	BSTNode *right;
    void initialize(int);
    void destroy();
    void add(BSTNode*);
};

struct BSTree {
	BSTNode *root;
    void initialize();
    void add(int);
    BSTNode* remove(int);
    BSTNode* search(int);
    BSTNode* search_parent(int);
    void print_tree();
    void destroy();
};