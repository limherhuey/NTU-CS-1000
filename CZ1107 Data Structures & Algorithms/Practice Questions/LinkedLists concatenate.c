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
int concatenate(ListNode **ptrHead1, ListNode *head2);

////////////////////////////////////////////////////////////////////

int main()
{
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

    printf("\nBefore concatenate() is called:\n");
    printf("List 1:\n");
    printList(head1);
    printf("List 2:\n");
    printList(head2);

    concatenate(&head1, head2);

    printf("\nAfter concatenate() was called:\n");
    printf("The concatenated list:\n");
    printList(head1);

    if(head1!=NULL)
       deleteList(&head1);

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

////////////////////// my code ////////////////////////////////////
int concatenate(ListNode **ptrHead1, ListNode *head2){

    // if both linked lists are empty or only 2nd linked list is empty
	if ((*ptrHead1 == NULL && head2 == NULL) || head2 == NULL)
        return -1;

    // if 1st linked list is empty
    if (*ptrHead1 == NULL) {
        *ptrHead1 = head2;
        return 0;
    }

    // find final node of 1st linked list
    ListNode *cur = *ptrHead1;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    // link 1st to 2nd
    cur->next = head2;

    return 0;
}
