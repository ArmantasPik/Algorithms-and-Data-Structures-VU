#include <stdio.h>
#include <stdbool.h>

#include "BST.h"

int main()
{
	int a;

	//a = 6;
	//printf("%d\n", a);

	binarySearchTree* BST = createTree();

	for(int i=0; i<5; i++)
	{
		insert(BST, i);
		 printBST(BST->root);
		 printf("\n");
	}

	for(int i=9; i>5; i--)
	{
		insert(BST, i);
		 printBST(BST->root);
		 printf("\n");
	}

	BSTnode *node = find(BST, 3);
	if(node == NULL)
		printf("neradau");
	else
		printf("%d\n", node->data);

	insert(BST, -2);
	insert(BST, 0);
	insert(BST, 0);

	printf("AVL pries deletion:\n");
	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");


	deleteElement(BST, 9);


	printf("AVL istrinus 9:\n");
	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");


	deleteElement(BST, 8);

	printf("AVL istrinus 8:\n");
	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");


	deleteElement(BST, 3);

	printf("AVL istrinus 3:\n");
	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");



	deleteElement(BST, 1);

	printf("AVL istrinus 1:\n");
	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");

	insert(BST, 1);

	printf("AVL idejus 1:\n");
	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");

	insert(BST, 7);

	printf("AVL idejus 7:\n");
	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");

	deleteElement(BST, 4);

	printf("AVL istrinus 4:\n");
	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");

	for(int i=9; i<=1000; i++)
		insert(BST, i);
	for(int i=9; i<=1000; i++)
		deleteElement(BST, i);

	printBST(BST->root);
	traverseBST(BST->root);
	printf("\n\n");
	printf("baigiau darba\n");
	return 0;
}