////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;
typedef struct _linkedlist{
	ListNode *head;
	int size;
} LinkedList;
typedef struct _dbllistnode{
	int item;
	struct _dbllistnode *pre;
	struct _dbllistnode *next;
} DblListNode;

////////////////////////////////////////////////////////////////////
void printList(ListNode *cur);
ListNode * findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);
void deleteList(ListNode **ptrHead);

// these are for the practice questions
int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2);

////////////////////////////////////////////////////////////////////

int main()
{
    ListNode *combined = NULL;
    ListNode *head1=NULL;
    ListNode *head2=NULL;
    int size1 =0, size2 = 0;
    int item;

    printf("Enter a first list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head1,size1, item)) size1++;
    scanf("%*s");

    printf("Enter a second list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head2,size2, item)) size2++;
    scanf("%*s");

    printf("\nBefore combineAlternating() is called:\n");
    printf("List 1:\n");
    printList(head1);
    printf("List 2:\n");
    printList(head2);

    combineAlternating(&combined, head1, head2);

    printf("\nAfter combineAlternating() was called:\n");
    printf("The combined list:\n");
    printList(combined);

    if(combined!=NULL)
       deleteList(&combined);

    return 0;
}

void printList(ListNode *cur){
    printf("Current List: ");
    while (cur != NULL){
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode(ListNode* cur, int index)
{
   if (cur==NULL || index<0)
      return NULL;
   while(index>0){
      cur=cur->next;
      if (cur==NULL)
         return NULL;
      index--;
   }
   return cur;
}

int insertNode(ListNode **ptrHead, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode(*ptrHead, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        return 1;
    }
    return 0;
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }
    *ptrHead=NULL;
}

////////////////////////////// my code ////////////////////////////////

int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2){

    // both LinkedLists are empty
    if (head1 == NULL && head2 == NULL)
        return -1;
    // first LinkedList is empty
    else if (head1 == NULL) {
        *ptrHead = head2;
        return 0;
    }
    // second LinkedList is empty
    else if (head2 == NULL) {
        *ptrHead = head1;
        return 0;
    }

    // initialise first node
    *ptrHead = head1;
    ListNode *node = *ptrHead;
    head1 = head1->next;
    
    // alternate connections until either LinkedList ends
    while (head1 != NULL && head2 != NULL) {
        node->next = head2;
        head2 = head2->next;
        node = node->next;

        node->next = head1;
        head1 = head1->next;
        node = node->next;
    }

    // first LinkedList is first to finish, or both LinkedLists finish
    if (head1 == NULL) {
        node->next = head2;
    }
    else if (head2 == NULL) {
        node->next = head1;
    }

    return 0;
}
