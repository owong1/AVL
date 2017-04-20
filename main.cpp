#include <iostream>
#include "AVL.h"

using namespace std;

int main(){
	AVL tree;

	int values[] = { 55, 27, 68, 19, 32, 70, 105, 3, 21, 93, 5, 14 };
	tree.test(values, 12);

	cout << endl;

	int array[] = { 6, 2, 9, 7};
	tree.test(array, 4);

	getchar();
	return 0;
}