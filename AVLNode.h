#ifndef AVLNODE_H
#define AVLNODE_H

// AVL tree node
class AVLNode{
public:
	int keyVal;
	AVLNode* left;
	AVLNode* right;
	int height;
	AVLNode();
};

#endif