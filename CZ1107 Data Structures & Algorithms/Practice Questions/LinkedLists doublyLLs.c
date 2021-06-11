/////////////////////////// yes all my code /////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int item;
    struct _dbllistnode *pre;
    struct _dbllistnode *next;
} DblListNode;

int insertDbl(DblListNode **ptrHead, int index, int value);
void printDblList(DblListNode *head);
void rev_printDblList(DblListNode *head);

int main()
{
    DblListNode *dblHead = NULL;
    int item, index;

    while (1)
    {
        printf("Enter value to insert into the Doubly Linked List, terminate with any non-digit character:\n");
        if (!scanf("%d", &item))
            break;

        printf("Enter index to insert value into:\n");
        scanf("%d", &index);

        if (insertDbl(&dblHead, index, item) != 0)
        {
            printf("Error. Value could not be inserted at iloc %d.", index);
            return -1;
        }

        printDblList(dblHead);
        rev_printDblList(dblHead);
    }

    printDblList(dblHead);

    return 0;
}

int insertDbl(DblListNode **ptrHead, int index, int value)
{

    // invalid index: negative value
    if (index < 0)
        return -1;

    // adding to front of Doubly Linked List
    if (index == 0) {
        DblListNode *new = malloc(sizeof(DblListNode));
        new->item = value;
        new->next = *ptrHead;
        new->pre = NULL;

        *ptrHead = new;
        if (new->next != NULL) // if not the only item in the DLL
            new->next->pre = new;

        return 0;
    }

    // find node at index-1
    DblListNode *temp = *ptrHead;
    int i;
    for (i = 0; i < index - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    // invalid index: beyond the DLL
    if (temp == NULL)
        return -1;

    // insert new node at iloc
    DblListNode *new = malloc(sizeof(DblListNode));
    new->item = value;
    new->next = temp->next;
    new->pre = temp;

    temp->next = new;
    if (new->next != NULL) // if not last item in the DLL
        new->next->pre = new;

    return 0;
}

void printDblList(DblListNode *head)
{
    printf("The current Doubly Linked List:\n");
    while (head != NULL)
    {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

void rev_printDblList(DblListNode *head)
{
    printf("The current Doubly Linked List in reverse:\n");

    // traverse to last node
    while (head->next != NULL)
    {
        head = head->next;
    }

    // print in reverse order
    while (head != NULL)
    {
        printf("%d ", head->item);
        head = head->pre;
    }
    printf("\n");
}