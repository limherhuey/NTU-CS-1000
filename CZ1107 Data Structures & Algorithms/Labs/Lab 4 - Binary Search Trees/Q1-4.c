//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main()
{
	int i = 0;

	BTNode *root = NULL;

	//question 1
	do
	{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d", &i);
		if (i != -1)
			insertBSTNode(&root, i);
	} while (i != -1);

	//question 2
	printf("\n");
	printBSTInOrder(root);
	printf("\n");

	//question 3
	if (isBST(root, -1000000, 1000000) == 1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do
	{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d", &i);
		if (i != -1)
		{
			root = removeBSTNode(root, i);
			printBSTInOrder(root);
		}
	} while (i != -1);

	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
	// base case: empty BST
	if (*node == NULL)
	{
		*node = malloc(sizeof(BTNode));
		(*node)->item = value;
		(*node)->left = (*node)->right = NULL;
		return;
	}

	// value smaller than node, traverse left
	if (value < (*node)->item)
		insertBSTNode(&(*node)->left, value);
	// value larger than node, traverse right
	else if (value > (*node)->item)
		insertBSTNode(&(*node)->right, value);
}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	// base case: nothing to print
	if (node == NULL)
		return;

	// in-order printing
	printBSTInOrder(node->left);
	printf("%d ", node->item);
	printBSTInOrder(node->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max)
{
	if (node == NULL)
		return 1;

	// the item stored in node has to be smaller than max and larger than min
	if (node->item >= max || node->item <= min)
		return -1;

	// check left and right subtrees are BSTs
	if (isBST(node->left, min, node->item) == 1)
		return isBST(node->right, node->item, max);
	return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	BTNode *temp;

	// base case: empty BST
	if (node == NULL)
		return node;

	// if this node does not hold value
	// remove node from left/right subtree and update next pointers
	if (value < node->item)
		node->left = removeBSTNode(node->left, value);
	else if (value > node->item)
		node->right = removeBSTNode(node->right, value);

	// this node holds value and is to be removed
	else {
		// case 1: no children // case 2: 1 child
		if (node->left == NULL) {
			temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			temp = node->left;
			free(node);
			return temp;
		}
		// case 3: 2 children
		else {
			// find immediate successor (min value in right subtree)
			temp = findMin(node->right);
			// replace value with immediate successor value
			node->item = temp->item;
			// remove immediate successor node and replace right subtree
			node->right = removeBSTNode(node->right, temp->item);
		}
	}
	return node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	BTNode *temp = p;

	// empty BST
	if (p == NULL)
		return NULL;

	// traverse to last left node (smallest value)
	while (temp->left != NULL)
	{
		temp = temp->left;
	}

	return temp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
