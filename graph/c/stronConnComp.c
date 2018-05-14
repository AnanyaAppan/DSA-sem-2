#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int t = 1;
int Index;
 
struct node
{
    int vertex;
    int d;
    int f;
    struct node* next;
    struct node* parent;
};

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int** weightLists;
    char** color; 
};


void TopoSort(struct Graph* graph, struct node* vertex, struct node* vertices[],struct node* sorted[]) {
    struct node* temp = graph->adjLists[vertex->vertex];
    graph->color[vertex->vertex] = "yellow";
    vertices[vertex->vertex]->d = t++;

    while(temp!=NULL) {
        if(!strcmp(graph->color[temp->vertex],"red")){
            temp->parent = vertices[vertex->vertex];
            TopoSort(graph, temp, vertices,sorted);
            graph->color[temp->vertex] = "blue";
        }
        temp = temp->next;
    } 
    vertices[vertex->vertex]->f = t++;
    sorted[Index--] = vertices[vertex->vertex];
}

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

void addEdge(struct Graph* graph, struct node* src, struct node* dest)
{
    // Add edge from src to dest
    struct node* newNode = createNode(dest->vertex);
    if(graph->adjLists[src->vertex]==0)
    {
        graph->adjLists[src->vertex] = newNode;
    }
    else{
        newNode->next = graph->adjLists[src->vertex];
        graph->adjLists[src->vertex] = newNode;
    }
    // graph->weightLists[src->vertex][dest->vertex] = weight;
    // // Add edge from dest to src
    // newNode = src;
    // newNode->next = graph->adjLists[dest->vertex];
    // graph->adjLists[dest->vertex] = newNode;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void DFS(struct Graph* graph, struct node* vertex, struct node* vertices[]) {
    struct node* temp = graph->adjLists[vertex->vertex];
    graph->color[vertex->vertex] = "yellow";
    vertices[vertex->vertex]->d = t++;
    printf("->%d ", vertex->vertex);

    while(temp!=NULL) {
        if(!strcmp(graph->color[temp->vertex],"red")){
            temp->parent = vertices[vertex->vertex];
            DFS(graph, temp, vertices);
            graph->color[temp->vertex] = "blue";
        }
        temp = temp->next;
    } 
    vertices[vertex->vertex]->f = t++;     
}

struct Graph* transpose(struct Graph* graph, struct node* vertices[])
{
    int num = graph->numVertices;
    struct Graph* g = createGraph(num);
    for(int i=0;i<num;i++)
    {
        struct node* temp = graph->adjLists[i];
        while(temp)
        {
            addEdge(g ,vertices[temp->vertex], vertices[i]);  
            temp = temp->next;
        }
    }
    return g;
}

int StronglyConn(struct Graph* graph, struct node* vertices[])
{
    int num = graph->numVertices;
    struct Graph* graphT = transpose(graph, vertices);
    struct node* sorted[num+1];
    TopoSort(graph, vertices[0], vertices, sorted);
    for(int i=0;i<num-1;i++)
    {
        if(!strcmp(graphT->color[i],"red"))
        {
            DFS(graphT,sorted[i], vertices);
            printf("\n");
        }
    }
    return 0;
}

int main()
{
    printf("enter num of nodes\n");
    int n;
    scanf("%d",&n);
    Index = n-1;
    struct Graph* graph = createGraph(n+1);
    struct node* vertices[n+1];
    for(int i=0;i<=n;i++) vertices[i] = 0;
    printf("enter num of edges\n");
    int edges;
    scanf("%d",&edges);
    printf("enter the edges\n");
    while(edges--)
    {
        int start, end;
        scanf("%d %d",&start,&end);
        start--;
        end--;
        if(!vertices[start]) vertices[start] = createNode(start);
        if(!vertices[end]) vertices[end] = createNode(end);
        addEdge(graph, vertices[start], vertices[end]);
    }
    printf("the strongly connected components are\n");
    StronglyConn(graph, vertices);
    return 0;
}