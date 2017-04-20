#include <iostream>
#include "AVL.h"


AVL::~AVL(){	//dtor
	deleteTree(root);
}

void AVL::deleteTree(AVLNode *leaf){			//private member: recursively delete nodes
	if (leaf != NULL){							//search while there is a non-NULL nodes
		deleteTree(leaf->left);					//leftmost leaf node
		deleteTree(leaf->right);				//right child leaf node from leftmost's parent node
		delete leaf;
	}
}


//allocates a new node with the given key and
//NULL left and right pointers
AVLNode::AVLNode(){
	left = right = NULL;
	height = 1;  // new node is initially added at leaf
}

//get height of the tree
int AVL::height(AVLNode* n){
	if (n == NULL){				//if no node, height is 0
		return 0;
	}
	return n->height;
}

int AVL::height(){				//public height function
	return height(root);
}

// get Balance factor of Node n as root
int AVL::getBalance(AVLNode *n){
	if (n == NULL){
		return 0;
	}
	//balance = height of left subtree - height of right subtree
	return height(n->left) - height(n->right);
}

int AVL::getBalance(){
	return getBalance(root);
}

void AVL::fixHeight(AVLNode* n){
	int leftHeight = height(n->left);
	int rightHeight = height(n->right);
	//height of root = height of subtree with greater height + 1 for root's height
	n->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

//right rotate subtree rooted with b
AVLNode* AVL::rightRotate(AVLNode *b){
	AVLNode* a = b->left;
	AVLNode* temp = a->right;

	//rotate
	a->right = b;
	b->left = temp;

	// update heights
	fixHeight(b);
	fixHeight(a);
	
	// return changed root
	return a;

}


//left rotate subtree rooted with a
AVLNode* AVL::leftRotate(AVLNode *a){
	AVLNode* b = a->right;
	AVLNode* temp = b->left;

	b->left = a;
	a->right = temp;

	//update heights
	fixHeight(a);
	fixHeight(b);

	// return changed root
	return b;

}

AVLNode* AVL::insert(int key, AVLNode* leaf){			//private insert

	if (leaf == NULL){
		leaf = new AVLNode;
		leaf->keyVal = key;				//leaf's value becomes input key
		return(leaf);
	}

	//recursively check either left or right until empty node
	if (key < leaf->keyVal){
		leaf->left = insert(key, leaf->left);
	}
	else{
		leaf->right = insert(key, leaf->right);
	}

	// update height of parent node
	fixHeight(leaf);

	// get the Balance factor of this parent node to check whether
	//this node became unbalanced
	int balance = getBalance(leaf);

	//if this node becomes unbalanced, there are 4 cases:
	// Single rotation
	// Left Left Case: LL
	if (balance > 1 && key < leaf->left->keyVal){
		return rightRotate(leaf);
	}
	// Right Right Case: RR
	if (balance < -1 && key > leaf->right->keyVal){
		return leftRotate(leaf);
	}

	// Double rotation
	// Left Right Case: LR
	if (balance > 1 && key > leaf->left->keyVal){
		leaf->left = leftRotate(leaf->left);
		return rightRotate(leaf);
	}
	// Right Left Case: RL
	if (balance < -1 && key < leaf->right->keyVal){
		leaf->right = rightRotate(leaf->right);
		return leftRotate(leaf);
	}

	//return the node(leaf) pointer (unchanged)
	return leaf;
}

void AVL::insert(int key){
	if (root != NULL){
		insert(key, root);
	}
	else{
		root = new AVLNode;
		root->keyVal = key;
		root->left = NULL;
		root->right = NULL;
	}
}

//private print AVL tree in order: left root right
//use indentation and new lines for a clearer tree display
void AVL::printTree(AVLNode* leaf, int indent){		
	if (leaf != NULL){
		if (leaf->left != NULL){
			printTree(leaf->left, indent + 1);
		}
		for (int i = 0; i < 3 * indent; i++){		//increase indentation for each leaf
			std::cout << ' ';
		}
		std::cout << leaf->keyVal << std::endl;		//output value then use new line
		if (leaf->right != NULL){
			printTree(leaf->right, indent + 1);
		}
	}
	else{
		std::cout << "Tree is empty" << std::endl;
	}
}

void AVL::printTree(){				//public print
	printTree(root, 0);
}

void AVL::test(int arr[], int size){
	AVL tree;

	std::cout << "Values to insert: " << std::endl;
	for (int i = 0; i < size; i++){
		std::cout << arr[i] << " ";
		tree.insert(arr[i]);
	}
	std::cout << "\nConstructed AVL tree with root left to right: " << std::endl;
	tree.printTree();

	std::cout << "\nHeight of tree: " << tree.height() << std::endl;
	std::cout << "Balance of tree: " << tree.getBalance() << std::endl;

}