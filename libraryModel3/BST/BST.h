#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdbool.h>


///variable that stores data
///must have comparison operators (<, >)
typedef int VAR;

typedef struct BSTnode
{
	VAR data;
	int height;
	struct BSTnode *left;
	struct BSTnode *right;
	struct BSTnode *parent;
} BSTnode;

typedef struct binarySearchTree
{
	BSTnode *root;
}binarySearchTree;

binarySearchTree* createTree();

bool insert(binarySearchTree* tree, VAR newVal);

void deleteBST(BSTnode* root);

void traverseBST(BSTnode* root);

int height(BSTnode *x);

int balance(BSTnode *n);

void printBST(BSTnode *n);

BSTnode* find(binarySearchTree *tree, VAR val);

bool deleteElement(binarySearchTree *tree, VAR val);

#endif