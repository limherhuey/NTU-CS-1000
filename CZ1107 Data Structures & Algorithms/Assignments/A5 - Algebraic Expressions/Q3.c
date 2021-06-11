#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode; // You should not change the definition of BTNode

typedef struct _node
{
    BTNode *item;
    struct _node *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode **root, char *prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr, BTNode *item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode *root = NULL;

    printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode **root, char *prefix) {
    Stack s;
    s.head = NULL;
    s.size = 0;

    while (*prefix != '\0') {
        // operand
        if (*prefix >= '0' && *prefix <= '9')
        {
            // get complete number
            int num = 0, digit;
            while (*prefix != '\0' && *prefix != ' ') {
                digit = (int) (*prefix - '0');
                num = num * 10 + digit;
                prefix++;
            }

            // leaf node
            BTNode *new = malloc(sizeof(BTNode));
            new->item = num;
            new->left = new->right = NULL;

            // get parent node from stack
            BTNode *parent = peek(s);

            // assign new node as left child
            if (parent->left == NULL)
                parent->left = new;
            // assign new node as right child & pop parent from stack
            else {
                parent->right = new;
                pop(&s);
            }

            if (*prefix == '\0')
                break;
        }
        // operator
        else if (*prefix != ' ') {
            // new node
            BTNode *new = malloc(sizeof(BTNode));
            new->item = *prefix;
            new->left = new->right = NULL;

            if (*root == NULL) // root node
                *root = new; 
            else { // internal node
                // get parent node from stack
                BTNode *parent = peek(s);

                // assign new node as left child
                if (parent->left == NULL)
                    parent->left = new;
                // assign new node as right child & pop parent from stack
                else {
                    parent->right = new;
                    pop(&s);
                }
            }

            // push new operator node to stack
            push(&s, new);
        }

        prefix++;
    }
}

void printTree(BTNode *node)
{ /* prints tree by in-order traversal, which is the infix expression */

    // base case: nothing to print
    if (node == NULL)
        return;
    
    // print left subtree
    printTree(node->left);

    // print current node's item
    if (node->left == NULL && node->right == NULL)
        printf("%d ", node->item); // operand
    else
        printf("%c ", node->item); // operator

    // print right subtree
    printTree(node->right);
}

void printTreePostfix(BTNode *node)
{ /* prints tree by post-order traversal, which is the postfix expression */

    // base case: nothing to print
    if (node == NULL)
        return;
    
    // print left & right subtrees
    printTreePostfix(node->left);
    printTreePostfix(node->right);

    // print current node's item
    if (node->left == NULL && node->right == NULL)
        printf("%d ", node->item); // operand
    else
        printf("%c ", node->item); // operator
}

double computeTree(BTNode *node)
{
    // empty
    if (node == NULL)
        return 0;
    
    // operand: return its own value
    if (node->left == NULL && node->right == NULL)
        return node->item;
    // operator: evaluate expression
    else {
        switch (node->item) {
            case '+':
                return computeTree(node->left) + computeTree(node->right);
            case '-':
                return computeTree(node->left) - computeTree(node->right);
            case '*':
                return computeTree(node->left) * computeTree(node->right);
            case '/':
                return computeTree(node->left) / computeTree(node->right);
        }
    }
}

void push(Stack *sPtr, BTNode *item)
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

BTNode *peek(Stack s)
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

void deleteTree(BTNode **root)
{
    BTNode *temp;
    if (*root != NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}



// _________________________ Attempt 1 - _____________________________
// ____ need to store whether item is operator or operand in node :( ___
// void createExpTree2(BTNode **root, char *prefix)
// {
//     while (*prefix != '\0')
//     {
//         if (*prefix >= '0' && *prefix <= '9')
//         {
//             // get complete number
//             int num = 0, digit;
//             while (*prefix != '\0' && *prefix != ' ') {
//                 digit = (int) (*prefix - '0');
//                 num = num * 10 + digit;
//                 prefix++;
//             }
//             printf("number is %d\n", num);

//             // insert operand at correct place in binary tree
//             preOrderInsertion(root, num);

//             if (*prefix == '\0')
//                 break;
//         }
//         else if (*prefix != ' ')
//         {
//             printf("pot\n");

//             preOrderInsertion(root, *prefix);
//         }

//         prefix++;
//     }
// }

// int preOrderInsertion(BTNode **node, int c)
// {
//     // base case: insert item
//     if (*node == NULL)
//     {
//         *node = malloc(sizeof(BTNode));
//         (*node)->item = c;
//         (*node)->left = (*node)->right = NULL;

//         printf("item %d inserted\n\n", c);

//         return 0;
//     }

//     // traverse left then right subtree to find first available position to insert at
//     // only traverse if next node is not an operand (leaf node, so no more insertion to be done)
//     if ((*node)->left == NULL || !((*node)->left->item >= '0' && (*node)->left->item <= '9')) {
//         printf("going left...\n");
//         if (preOrderInsertion(&(*node)->left, c) == 0)
//             return 0;
//     }
//     if ((*node)->right == NULL || !((*node)->right->item >= '0' && (*node)->right->item <= '9')) {
//         printf("going right...\n");
//         return preOrderInsertion(&(*node)->right, c);
//     }

//     printf("item %d not inserted\n\n");

//     return 1;
// }
// ___________________________________________________________