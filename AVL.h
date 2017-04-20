#ifndef AVL_H
#define AVL_H
#include "AVLNode.h"


class AVL{
private:
	AVLNode* insert(int key, AVLNode* leaf);	//balance after inserting value
	int height(AVLNode *node);
	int getBalance(AVLNode *node);

	void printTree(AVLNode* leaf, int indent);
public:
	AVLNode* root;
	AVL(){					//ctor
		root = NULL;
	}
	~AVL();

	int height();
	int getBalance();
	void fixHeight(AVLNode* n);

	AVLNode* rightRotate(AVLNode *b);		//rotate right if node is left
	AVLNode* leftRotate(AVLNode *a);		//rotate left if node is right

	void insert(int key);	//balance after inserting value
	void printTree();
	void deleteTree(AVLNode* leaf);

	void test(int arr[], int size);
};

#endif