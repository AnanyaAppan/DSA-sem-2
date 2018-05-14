#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int t = 1;
 
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


void DFS(struct Graph* graph, struct node* vertex, struct node* vertices[]) {
    printf("t = %d\n",t);
    struct node* temp = graph->adjLists[vertex->vertex];
    graph->color[vertex->vertex] = "yellow";
    vertices[vertex->vertex]->d = t++;
    printf("Visited %d \n", vertex->vertex);

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

int cycleDetect(struct Graph* graph, struct node* vertices[])
{
    for(int i=0;i<graph->numVertices;i++)
    {
        struct node* temp = graph->adjLists[i];
        while(temp)
        {
            if(vertices[temp->vertex]->f > vertices[i]->f &&  vertices[i]->f!=0) return 1;
            temp = temp->next;
        }
    }
    return 0;
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
        int start, end;
        scanf("%d %d",&start,&end);
        start--;
        end--;
        if(!vertices[start]) vertices[start] = createNode(start);
        if(!vertices[end]) vertices[end] = createNode(end);
        addEdge(graph, vertices[start], vertices[end]);
    }
    printf("enter start node\n");
    int start;
    scanf("%d",&start);
    start--;
    vertices[start]->parent = 0;
    DFS(graph, vertices[start], vertices);
    for(int i=0;i<n;i++)
    {
        printf("vertex %d d = %d f = %d\n", i, vertices[i]->d, vertices[i]->f);
    }
    if(cycleDetect(graph, vertices)) printf("hey!! there's a a cycle\n");
    else printf("oops!..no cycle\n");
    return 0;
}