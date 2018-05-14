#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int t = 1;
int edgeIndex=0;

struct Edge{
    int start;
    int weight;
    int end;
};

int merge(struct Edge* arr[],int i, int k, int j)
{
    int left = i, right = k+1;
    struct Edge* B[100];
    int p=i;
    while(left<k+1 && right<j+1)
    {
        if(arr[left]->weight<arr[right]->weight)
        {
            B[p++] = arr[left++];
        }
        else
        {
            B[p++] = arr[right++];
        }
    }
    while(left<=k)
    {
        B[p++] = arr[left++];
    }
    while(right<=j)
    {
        B[p++] = arr[right++];
    }
    for(int n=i;n<=j;n++) arr[n] = B[n];
    return 0;
}

int mergeSort(struct Edge* arr[],int i,int j)
{
    if(i==j) return 0;
    int k = (i+j)/2;
    mergeSort(arr,i,k);
    mergeSort(arr,k+1,j);
    merge(arr,i,k,j);
    return 0;
}

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
    int numEdges;
    int* C;
    int* S;
    struct Edge** edges;
};

int Krushkals(struct Graph* graph, struct node* vertices[])
{
    mergeSort(graph->edges, 0,graph->numEdges-1);
    for(int i=0;i<graph->numEdges;i++)
    {
        struct Edge* e = graph->edges[i];
        int color1 = graph->C[e->start];
        int color2 = graph->C[e->end];
        if(color1 != color2)
        {
            printf("%d to %d\n",e->start+1, e->end+1);
            vertices[e->end]->parent = vertices[e->start];
            if(graph->S[color1] > graph->S[color2])
            {
                graph->C[e->end] = color1;
                for(int i=0;i<graph->numVertices;i++)
                {
                  if(C[i]==color2) C[i] = color1;
                }
                graph->S[color1] += graph->S[color2];
                graph->S[color2] = 0;
            }
            else{
                graph->C[e->start] = color2;
                for(int i=0;i<graph->numVertices;i++)
                {
                  if(C[i]==color1) C[i] = color2;
                }
                graph->S[color2] += graph->S[color1];
                graph->S[color1] = 0;
            }
        }
    }
    return 0;
}

struct Graph* createGraph(int vertices, int edges)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->numEdges = edges;

    graph->C = (int*)malloc(vertices*sizeof(int));
    for(int i=0;i<vertices;i++) graph->C[i] = i;

    graph->S = (int*)malloc(vertices*sizeof(int));
    for(int i=0;i<vertices;i++) graph->S[i] = 1;

    graph->edges = (struct Edge**)malloc(edges*sizeof(struct Edge*));
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    struct Edge* e = malloc(sizeof(struct Edge));
    e->start = src;
    e->end = dest;
    e->weight = weight;
    graph->edges[edgeIndex++] = e;
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
    struct node* vertices[n+1];
    for(int i=0;i<=n;i++) vertices[i] = 0;
    printf("enter num of edges\n");
    int edges;
    scanf("%d",&edges);
    struct Graph* graph = createGraph(n+1,edges);
    printf("enter the edges\n");
    while(edges--)
    {
        int start, end, weight;
        scanf("%d %d %d",&start,&end, &weight);
        start--;
        end--;
        if(!vertices[start]) vertices[start] = createNode(start);
        if(!vertices[end]) vertices[end] = createNode(end);
        addEdge(graph, start, end, weight);
    }
    Krushkals(graph, vertices );
    return 0;
}
