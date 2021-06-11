#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The limit of expression length

typedef struct _stackNode
{
    double item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);

double exePostfix(char *);
double evaluate(double a, double b, char c); // utility function
double realpop(Stack *s);                    // utility function

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    gets(postfix);

    printf("The answer is %.2lf.\n", exePostfix(postfix));

    return 0;
}

double exePostfix(char *postfix)
{
    Stack s;
    s.head = NULL;
    s.size = 0;
    double a, b;

    while (*postfix != '\0')
    {
        // push operands to stack
        if (isdigit(*postfix))
            // convert char to double
            push(&s, (double)(*postfix - '0'));

        // when an operator is encountered
        else
        {
            // pop 2 operands from stack to evaluate
            b = realpop(&s);
            a = realpop(&s);

            // push result of evaluation onto stack
            push(&s, evaluate(a, b, *postfix));
        }
        postfix++;
    }

    // final result
    return realpop(&s);
}

double evaluate(double a, double b, char c)
{ /* evaluates an expression a c b, where c is an operator */
    switch (c)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
}

double realpop(Stack *s)
{ /* Returns popped item on stack */
    if (s->head == NULL)
    {
        printf("no items to pop from stack\n");
        return -1;
    }

    double item = peek(*s);
    pop(s);
    return item;
}

void push(Stack *sPtr, double item)
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

double peek(Stack s)
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
