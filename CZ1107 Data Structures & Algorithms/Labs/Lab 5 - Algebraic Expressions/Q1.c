#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The limit of expression length

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

void in2Post(char *, char *);
int precedence(char a); // utility function
int realpop(Stack *s);   // utility function

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Post(infix, postfix);
    printf("The postfix expression is \n");
    printf("%s\n", postfix);
    return 0;
}

void in2Post(char *infix, char *postfix)
{
    Stack s;
    s.size = 0;
    s.head = NULL;
    int i = 0;
    int c;

    while (*infix != '\0')
    {
        // operand: add to postfix string
        if (isalnum(*infix))
            postfix[i++] = *infix;
        // open bracket: push to stack
        else if (*infix == '(')
            push(&s, *infix);
        // close bracket: pop operators from stack and add to postfix string (in stack's order) until open bracket is encountered
        else if (*infix == ')')
            while ((c = realpop(&s)) != '(')
                postfix[i++] = c;
        // other operators
        else
        {
            // 1. if precedence of operator on top of stack >= current operator, pop operators from stack and add to postfix string
            // 1.1. until empty, open bracket on top of stack, or top operator has lower precedence
            while (!isEmptyStack(s) && peek(s) != '(' && precedence(peek(s)) >= precedence(*infix))
                postfix[i++] = realpop(&s);

            // 1.2. then push current operator onto stack
            // 2. if precedence of operator on top of stack < current operator, empty stack, or open bracket on top, push current operator onto stack
            push(&s, *infix);
        }

        infix++;
    }

    // add remaining operators to back of postfix string
    while (!isEmptyStack(s))
        postfix[i++] = realpop(&s);

    // end postfix string
    postfix[i] = '\0';
}

int precedence(char a)
{ /* Returns the rank of precedence of an operator; higher number means higehr precedence */

    // + and - are lower
    if (a == '+' || a == '-')
        return 1;
    // * and / are higher
    return 2;
}

int realpop(Stack *s)
{ /* Returns popped item on stack */
    if (s->head == NULL)
    {
        printf("no items to pop from stack\n");
        return -1;
    }

    int item = peek(*s);
    pop(s);
    return item;
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
