// ___________ Project Matching ____________

#include <stdio.h>
#include <stdlib.h>

// Graph
typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
    int source;
    int sink;
} Graph;

int maxMatch(Graph g);
int DFS(Graph g, int *parent);
void buildGraph(Graph *g, int S, int P, int M);
void printGraph(Graph g);
void linkVertex(ListNode **head, int child);
void unlinkVertex(ListNode **head, int child);

// DFS implementation - using Stack
typedef ListNode StackNode;
typedef struct _stack {
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);

// __________________________________________


int main() {
    // no. of Students, Projects, Mentors
    int S, P, M;
    scanf("%d %d %d", &S, &P, &M);

    // build graph
    Graph g;
    buildGraph(&g, S, P, M);
    printGraph(g);

    // find no. of maximum matches
    int maxm = maxMatch(g);
    printf("%d\n", maxm);
    return 0;
}


// __________________________________________

// finds max. no. of matches using Ford Fulkerson algorithm
int maxMatch(Graph gf) {
    int *parent = (int *) malloc(sizeof(int) * gf.V);
    int u, v;

    // while there is a valid augmented path (within 'parent')
    while (DFS(gf, parent)) {
        // for each edge in the path, update gf
        v = gf.sink; u = parent[v];
        while (u != -1) {
            unlinkVertex(&(gf.list[u]), v); // remove edge (u, v)
            linkVertex(&(gf.list[v]), u);   // insert edge (v, u)
            v = u; u = parent[v];
        }
    }

    // count g.sink neighbours/children (= max match)
    ListNode *tmp = gf.list[gf.sink];
    u = 0;
    while (tmp != NULL) {
        u++;
        tmp = tmp->next;
    }
    return u;
}

// searches for a path in g using DFS & returns success (1) or failure (0)
int DFS(Graph g, int *parent) {
    Stack s; s.head = NULL; s.size = 0;
    ListNode *tmp;
    int u;
    int *visited = (int *) malloc(sizeof(int) * g.V);

    // clear parent & visited arrays
    for (u = 0; u < g.V; u++) {
        parent[u] = -1;
        visited[u] = 0;
    }

    // find a path from g.source to g.sink
    push(&s, g.source);
    visited[g.source] = 1;
    while (!isEmptyStack(s)) {
        u = peek(s); pop(&s);       // get vertex from top of stack
        if (u == g.sink) break;     // sink encountered: a path is found
        // push all its unvisited children onto stack while updating parent array
        tmp = g.list[u];
        while (tmp != NULL) {   
            if (visited[tmp->vertex] == 0) {
                push(&s, tmp->vertex);
                visited[tmp->vertex] = 1;
                parent[tmp->vertex] = u;  // "parent[v] = u": u is the parent of v
            }
            tmp = tmp->next;
        }
    }

    // no path found from source to sink
    if (parent[g.sink] == -1)
        return 0;

    return 1;
}

// builds a tripartite based on input
// Project vertexes: 0 to P-1  // Student(1): P to P+S-1, Student(2): P+S to P+2S-1 // Mentor: P+2S to P+2S+M-1
void buildGraph(Graph *g, int S, int P, int M) {
    int i, j;
    int np, nm, k; 

    g->V = P + 2*S + M + 2;   // +2 for source S+P+M and sink S+P+M+1
    g->list = (ListNode **) malloc(sizeof(ListNode*) * g->V);
    for (i = 0; i < g->V; i++) 
        g->list[i] = NULL;
    
    // link source to all projects
    g->source = P + 2*S + M;
    for (i = 0; i < P; i++)
        linkVertex(&(g->list[g->source]), i);
    // link all mentors to sink
    g->sink = P + 2*S + M + 1;
    for (i = 0; i < M; i++)
        linkVertex(&(g->list[P+2*S+i]), g->sink);
    g->E = P + M;
    
    for (i = 0; i < S; i++) {
        scanf("%d %d", &np, &nm);   // no. of preference projects & mentors
        g->E += np + nm + 1;        // increment no. of edges  // +1 for Si(1) -> Si(2)

        // link preference projects to student i(1)
        for (j = 0; j < np; j++) {
            scanf("%d", &k);
            linkVertex(&(g->list[k-1]), P+i);
        }
        // link student i(1) to student i(2)
        linkVertex(&(g->list[P+i]), P+S+i);
        // link student i(2) to preference mentors
        for (j = 0; j < nm; j++) {
            scanf("%d", &k);
            linkVertex(&(g->list[P+S+i]), P+2*S+k-1);
        }
    }
}

// prints an adjacency list graph
void printGraph(Graph g) {
    if (g.list == NULL) {
        printf("Error.\n");
        return;
    }

    int i, edgecount = 0;
    ListNode *tmp;

    for (i = 0; i < g.V; i++) {
        printf("%d: ", i);
        tmp = g.list[i];
        while (tmp != NULL) {
            edgecount++;
            printf("%d -> ", tmp->vertex);
            tmp = tmp->next;
        }
        printf("\n");
    }

    if (edgecount == g.E)
        printf("Graph has %d edges.\n", g.E);
    else
        printf("Edge count incorrect, %d / %d.\n", edgecount, g.E);
}

// inserts a link between parent vertex (head) and child
void linkVertex(ListNode **head, int child) {
    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    new->vertex = child;
    new->next = *head;
    *head = new;
}

// removes a link between parent vertex (head) and child
void unlinkVertex(ListNode **head, int child) {
    ListNode *tmp = *head, *pre;
    while (tmp != NULL) {
        if (tmp->vertex == child)
            break;
        pre = tmp;
        tmp = tmp->next;
    }

    if (tmp == *head && tmp != NULL)
        *head = (*head)->next;
    else if (tmp != NULL)
        pre->next = tmp->next;
    free(tmp);
}

// ______________ Stack functions ______________

void push(Stack *sPtr, int vertex)
{
    StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

int isEmptyStack(Stack s)
{
    if(s.size==0) return 1;
    else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
    while(pop(sPtr));
}