#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType
{
    OPT,
    OPERAND
};

typedef struct _stackNode
{
    char item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

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

void in2PreLL(char *infix, LinkedList *inExpLL);
int prece(char a);      // utility function
char realpop(Stack *s); // utility function

void printExpLL(LinkedList inExpLL);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void in2PreLL(char *infix, LinkedList *inExpLL)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    // traverse to end of infix string
    char *tmp = infix, c;
    while (*(tmp++) != '\0');
    tmp -= 2;

    while (tmp >= infix)
    {
        // operand: add to LL
        if (*tmp >= '0' && *tmp <= '9')
        {
            // get complete number
            int digit, num = 0, exponent = 0, i;
            while (tmp >= infix && *tmp >= '0' && *tmp <= '9')
            {
                // get current digit with correct place value
                digit = (int)(*tmp - '0');
                for (i = 0; i < exponent; i++)
                    digit *= 10;

                // add to number
                num += digit;

                exponent++;
                tmp--;
            }
            tmp++;
            insertNode(inExpLL, num, OPERAND);
        }
        // start of bracket region: push bracket to stack
        else if (*tmp == ')')
            push(&s, *tmp);
        // end of bracket region:
        else if (*tmp == '(')
            while ((c = realpop(&s)) != ')')
                insertNode(inExpLL, c, OPT);
        // operator logic
        else
        {
            while (!isEmptyStack(s) && peek(s) != ')' && prece(peek(s)) > prece(*tmp))
                insertNode(inExpLL, realpop(&s), OPT);
            push(&s, *tmp);
        }

        tmp--;
    }

    // add all remaining operators in stack to LL
    while (!isEmptyStack(s))
        insertNode(inExpLL, realpop(&s), OPT);
}

int prece(char a)
{
    // precedence number of an operator
    if (a == '+' || a == '-')
        return 1;
    return 2;
}

char realpop(Stack *s)
{
    if (s == NULL || isEmptyStack(*s))
        return NULL;

    // remove and return item on top of the stack
    char item = peek(*s);
    pop(s);
    return item;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode *temp = NULL;
    temp = inExpLL.head;
    while (temp != NULL)
    {
        if (temp->type == OPERAND)
            printf(" %d ", temp->item);
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
    {
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

void push(Stack *sPtr, char item)
{
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

char peek(Stack s)
{
    return s.head->item;
}

int isEmptyStack(Stack s)
{
    if (s.size == 0)
        return 1;
    else
        return 0;
}
