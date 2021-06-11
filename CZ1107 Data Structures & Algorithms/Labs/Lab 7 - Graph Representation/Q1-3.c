#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    
    calDegreeV(g,degreeV);
    
    printGraphMatrix(g);
    printDegreeV(degreeV,g.V);
    
    adjM2adjL(&g);
    
    calDegreeV(g,degreeV);

    printGraphList(g);
    printDegreeV(degreeV,g.V);

    adjL2adjM(&g);
    printGraphMatrix(g);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    if(g.type == ADJ_LIST) {printf("Error"); return;}

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }

}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Question 1: convert adjacency matrix to adjacency list
void adjM2adjL(Graph *g) { 
    int i, j;
    ListNode **adjlist;

    if (g->type == ADJ_LIST) {
        printf("Already an adjacency list!\n");
        return;
    }

    adjlist = malloc(sizeof(ListNode *) * g->V);    // array of g->V no. of ListNode pointers

    for (i = 0; i < g->V; i++) {
        adjlist[i] = NULL;

        for (j = 0; j < g->V; j++) {
            // add new node for j in i's list if it is connected to i
            if (g->adj.matrix[i][j] == 1) {
                ListNode *new = malloc(sizeof(ListNode));
                new->vertex = j+1;
                new->next = adjlist[i];
                adjlist[i] = new;
            }
        }
    }
    
    g->adj.list = adjlist;
    g->type = ADJ_LIST;
}

// Question 2: convert adjacency list to adjacency matrix
void adjL2adjM(Graph *g){
    int i, j;
    int **adjmatrix;

    if (g->type == ADJ_MATRIX) {
        printf("Already an adjacency matrix!\n");
        return;
    }

    adjmatrix = malloc(sizeof(int *) * g->V);   // array of g->V no. of int pointers (/arrays)

    for (i = 0; i < g->V; i++) {
        // create an array sized g->V for each row i & populate with 0s
        adjmatrix[i] = malloc(sizeof(int) * g->V);
        for (j = 0; j < g->V; j++)
            adjmatrix[i][j] = 0;

        // traverse list i and transfer all edges to adjacency matrix
        ListNode *tmp = g->adj.list[i];
        while (tmp != NULL) {
            adjmatrix[i][tmp->vertex-1] = 1;
            tmp = tmp->next;
        }
    }

    g->adj.matrix = adjmatrix;
    g->type = ADJ_MATRIX;
}

// Question 3: compute vertex degrees using adjacent lists and adjacent matrix
void calDegreeV(Graph g, int *degreeV)
{   
    int i, j;
    
    // reset all degree counts to 0
    for (i = 0; i < g.V; i++)
        degreeV[i] = 0;

    if (g.type == ADJ_MATRIX) {
        for (i = 0; i < g.V; i++) 
            for (j = 0; j < g.V; j++) 
                if (g.adj.matrix[i][j] == 1)
                    degreeV[i]++;
    }
    else {
        for (i = 0; i < g.V; i++) {
            ListNode *tmp = g.adj.list[i];
            while (tmp != NULL) {
                degreeV[i]++;
                tmp = tmp->next;
            }
        }
    }
}

