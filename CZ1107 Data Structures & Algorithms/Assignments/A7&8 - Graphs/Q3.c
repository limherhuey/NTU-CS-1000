// ___________ SumToC ____________

#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
	int *itemArray;
	int sizeArray; //the size of a possible sequence
	struct _arraynode *next;
} ArrayNode;

typedef struct _arraylist
{
	int size; //the number of possible sequences
	ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist
{
	int sum;
	int size;
	ListNode *head;
} LinkedList;

// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////

void sumToC(LinkedList *ll, int C, ArrayList *al);
int main()
{
	int C;
	printf("Enter a number:\n");
	scanf("%d", &C);

	LinkedList ll;
	ll.head = NULL;
	ll.sum = 0;
	ll.size = 0;
	ArrayList al;
	al.head = NULL;
	al.size = 0;

	sumToC(&ll, C, &al);

	//printing all possible sequences
	ArrayNode *temp;
	int i, j;
	temp = al.head;
	for (i = 0; i < al.size; i++)
	{
		for (j = 0; j < temp->sizeArray; j++)
			printf(" %d ", temp->itemArray[j]);
		printf("\n");
		temp = temp->next;
	}

	return 0;
}

void sumToC(LinkedList *ll, int C, ArrayList *al)
{
	int i, n;

	// base case: sequence found
	if (C == 0) {
		// add sequence to back of ArrayList
		ArrayNode *new = (ArrayNode *)malloc(sizeof(ArrayNode));
		new->sizeArray = ll->size;
		new->itemArray = (int *)malloc(sizeof(int) * new->sizeArray);
		new->next = NULL;
		if (al->head == NULL)
			al->head = new;
		else {
			ArrayNode *tmp = al->head;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
		al->size++;

		// add array items from back to front
		ListNode *tmp = ll->head;
		i = 0;
		while (tmp != NULL) {
			new->itemArray[new->sizeArray - i++ - 1] = tmp->item;
			tmp = tmp->next;
		}
		return;
	}

	// start iteration from calling function + 1
	if (ll->head == NULL) n = 1;
	else n = ll->head->item + 1;

	// iterate through numbers n to C   //   doesn't search if n > C
	for (i = n; i <= C; i++) {
		// add the number i to the sequence
		insertNode(ll, 0, i);

		// recursion to find sequence of C - i
		sumToC(ll, C - i, al);

		// backtrack: remove i from sequence
		removeNode(ll, 0);
	}
}

///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	if (index == 0)
	{
		cur = ll->head;
		ll->head = (ListNode *)malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	return 0;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		ll->sum -= ll->head->item;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 1;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return 0;

		cur = pre->next;
		ll->sum -= cur->item;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 1;
	}

	return 0;
}

ListNode *findNode(LinkedList ll, int index)
{

	ListNode *temp;

	if (index < 0 || index >= ll.size)
		return NULL;

	temp = ll.head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
	ll->sum = 0;
}