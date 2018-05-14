#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 10000000

struct node
{
    int index;
    int vertex;
    int d;
    int f;
    struct node* next;
    struct node* parent;
    int p;
};

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    newNode->p = INF;
    return newNode;
}

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int** weightLists;
    char** color;
};

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = malloc(vertices * sizeof(struct node*));
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    graph->weightLists = (int**)malloc(vertices*sizeof(int*));

    for (i = 0; i < vertices; i++) {
        graph->weightLists[i] = (int*)malloc(vertices*sizeof(int));
    }

    graph->color = (char**)malloc(vertices*sizeof(char));
    for(int i=0;i<=vertices;i++)
    {
        graph->color[i] = (char*)malloc(7*sizeof(char));
        graph->color[i] = "red";
    }
    
    return graph;
}

void addEdge(struct Graph* graph, struct node* src, struct node* dest, int weight)
{
    // Add edge from src to dest
    struct node* newNode1 = createNode(dest->vertex);
    if(graph->adjLists[src->vertex]==0)
    {
        graph->adjLists[src->vertex] = newNode1;
    }
    else{
        newNode1->next = graph->adjLists[src->vertex];
        graph->adjLists[src->vertex] = newNode1;
    }
    graph->weightLists[src->vertex][dest->vertex] = weight;
    // Add edge from dest to src

    struct node* newNode2 = createNode(src->vertex);
    if(graph->adjLists[dest->vertex]==0)
    {
        graph->adjLists[dest->vertex] = newNode2;
    }
    else{
        newNode2->next = graph->adjLists[dest->vertex];
        graph->adjLists[dest->vertex] = newNode2;
    }
    graph->weightLists[dest->vertex][src->vertex] = weight;
}

void printGraph(struct Graph* graph)
{
    int n = graph->numVertices;
    for(int i=0;i<n;i++)
    {
        struct node* temp = graph->adjLists[i];
        printf("%d:",i);
        while(temp)
        {
            printf("%d->",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int BellmanFord(struct Graph* graph,struct node* s, struct node* vertices[])
{
    vertices[s->vertex]->parent = s;
    s->p = 0;
    for(int i=0;i<graph->numVertices;i++)
    {
        for(int j=0; j<graph->numVertices;j++)
        {
            struct node* temp = graph->adjLists[j];
            while(temp!=0)
            {
                if(vertices[temp->vertex]->p > vertices[j]->p + graph->weightLists[j][temp->vertex])
                {
                    vertices[temp->vertex]->p = vertices[j]->p + graph->weightLists[j][temp->vertex];
                    vertices[temp->vertex]->parent = vertices[j];
                }
                temp = temp->next;
            }
        }
    }
    return 0;
}

int printPath(int v, struct node* vertices[])
{
    if(vertices[v]->parent->vertex == v) printf("%d\n",v+1);
    else {
        printPath(vertices[v]->parent->vertex, vertices);
        printf("%d\n",v+1);
    }
    return 0;
}

int main()
{
    printf("enter num of nodes\n");
    int n;
    scanf("%d",&n);
    struct Graph* graph = createGraph(n+1);
    struct node* vertices[n+1];
    for(int i=0;i<=n;i++) vertices[i] = 0;
    printf("enter num of edges\n");
    int edges;
    scanf("%d",&edges);
    printf("enter the edges\n");
    while(edges--)
    {
        int start, end, weight;
        scanf("%d %d %d",&start,&end,&weight);
        start--;
        end--;
        if(!vertices[start]) 
        {
            vertices[start] = createNode(start);
        }
        if(!vertices[end]) 
        {
            vertices[end] = createNode(end);
        }
        addEdge(graph, vertices[start], vertices[end], weight);
        printf("edge added\n");
    }
    printGraph(graph);
    printf("enter start node\n");
    int start;
    scanf("%d",&start);
    start--;
    vertices[start]->parent = 0;
    BellmanFord(graph, vertices[start], vertices);
    for(int i=0;i<n;i++)
    {
        if(vertices[i]->parent!=0)
            printf("parent of %d is %d\n",i,vertices[i]->parent->vertex);
        else
            printf("root\n");
    }
    printf("enter the node u want to go to\n");
    int dest;
    scanf("%d",&dest);
    dest--;
    printf("the path to be taken is...\n");
    printPath(dest, vertices);
    return 0;
}