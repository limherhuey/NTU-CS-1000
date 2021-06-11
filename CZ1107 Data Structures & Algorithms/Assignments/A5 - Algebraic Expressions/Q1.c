#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType
{
    OPT,
    OPERAND
};

typedef struct _listnode
{
    int item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist
{
    int size;
    ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList(LinkedList ll);

void expressionLL(char *infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExpLL, int seed);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    expressionLL(infix, &inExpLL);

    int seed;
    printf("Enter a seed: \n");
    scanf("%d", &seed);
    printExpLL(inExpLL, seed);

    removeAllNodes(&inExpLL);
    return 0;
}

void expressionLL(char *infix, LinkedList *inExpLL)
{
    // traverse to end of string
    char *tmp = infix;
    while (*(tmp++) != '\0');
    tmp--;

    // add each char to LL, starting from the last char of infix
    while (--tmp >= infix)
    {
        // operand
        if (*tmp <= '9' && *tmp >= '0')
        {
            // get the complete number
            int num = 0, digit, exponent = 0;
            while (*tmp <= '9' && *tmp >= '0' && tmp >= infix)
            {
                // convert current digit to int in its supposed place value
                digit = (int)(*tmp - '0');
                for (int j = 0; j < exponent; j++)
                    digit *= 10;

                // add digit to number
                num = num + digit;

                // increment place value & move to next char
                exponent++;
                tmp--;
            }
            tmp++;

            // add number to linked list
            insertNode(inExpLL, num, OPERAND);
        }
        // operator
        else
        {
            insertNode(inExpLL, *tmp, OPT);
        }
    }
}

void printExpLL(LinkedList inExpLL, int seed)
{
    ListNode *temp = NULL;
    temp = inExpLL.head;
    while (temp != NULL)
    {
        if (temp->type == OPERAND)
            printf(" %d ", temp->item + seed);
        else
            printf(" %c ", (char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type)
{
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head = newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr)
{
    if (LLPtr == NULL || LLPtr->size == 0)
    { //Queue is empty or NULL pointer
        return 0;
    }
    else
    {
        ListNode *temp = LLPtr->head;
        LLPtr->head = LLPtr->head->next;

        free(temp);
        LLPtr->size--;
        return 1;
    }
}

int isEmptyLinkedList(LinkedList ll)
{
    if (ll.size == 0)
        return 1;
    else
        return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
    while (deleteNode(LLPtr))
        ;
}
