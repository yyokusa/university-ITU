#include <iostream>
#include <stdlib.h>

#include "tests.h"
#include "tree.h"
#include "bstree.h"

using namespace std;

void test_traversals(){
	Tree aTree;
	build_trivial_tree(aTree);
	
	inorder(aTree.root);
	cout<<endl;

	iter_inorder(aTree.root);
	cout<<endl;

	preorder(aTree.root);
	cout<<endl;

	postorder(aTree.root);
	cout<<endl;

	destroy_trivial_tree(aTree);
}

void test_bst(){
	BSTree atree;
	atree.initialize();
	atree.add(3);
	atree.add(1);
	atree.add(6);
	atree.add(2);
	atree.add(8);
	atree.add(5);
	atree.add(4);
	atree.add(7);

	atree.remove(1);
	atree.remove(6);
	atree.remove(2);
	atree.remove(4);
	atree.remove(3);
	atree.print_tree();
	cout << atree.search(8)->data << endl;

	atree.destroy();
}