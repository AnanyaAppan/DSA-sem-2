#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 1000000
int t = 1;
 
struct node
{
    int vertex;
    int d;
    int f;
    struct node* next;
    struct node* parent;
    int weight;
    int sumWeight;
    int leaf;
};

struct node* createNode(int v, int weight)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    newNode->parent = 0;
    newNode->weight = weight;
    newNode->leaf = 0;
    newNode->sumWeight = newNode->weight;
    return newNode;
}

struct Graph
{
    int numVertices;
    struct node** adjLists;
    char** color; 
};


int DFS(struct Graph* graph, struct node* vertex, struct node* vertices[]) {
    struct node* temp = graph->adjLists[vertex->vertex];
    graph->color[vertex->vertex] = "yellow";
    vertices[vertex->vertex]->d = t++;
    int sum = 0;
    while(temp!=NULL) {
        if(!strcmp(graph->color[temp->vertex],"red")){
            vertices[temp->vertex]->parent = vertices[vertex->vertex];
            printf("DFS = %d\n",DFS(graph, temp, vertices));
            sum +=  DFS(graph, temp, vertices);
            printf("sumw of %d= %d\n",temp->vertex,vertices[temp->vertex]->sumWeight);
            graph->color[temp->vertex] = "blue";
        }
        temp = temp->next;
    } 
    vertices[vertex->vertex]->f = t++; 
    vertices[vertex->vertex]->sumWeight += sum;
    return vertices[vertex->vertex]-> sumWeight;
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

    graph->color = (char**)malloc(vertices*sizeof(char));
    for(int i=0;i<=vertices;i++)
    {
        graph->color[i] = (char*)malloc(7*sizeof(char));
        graph->color[i] = "red";
    }
    
    return graph;
}

void addEdge(struct Graph* graph, struct node* src, struct node* dest,struct node* vertices[])
{
    // Add edge from src to dest
    struct node* newNode1 = createNode(dest->vertex,vertices[dest->vertex]->weight );
    if(graph->adjLists[src->vertex]==0)
    {
        graph->adjLists[src->vertex] = newNode1;
    }
    else{
        newNode1->next = graph->adjLists[src->vertex];
        graph->adjLists[src->vertex] = newNode1;
    }
    // Add edge from dest to src

    struct node* newNode2 = createNode(src->vertex, vertices[src->vertex]->weight);
    if(graph->adjLists[dest->vertex]==0)
    {
        graph->adjLists[dest->vertex] = newNode2;
    }
    else{
        newNode2->next = graph->adjLists[dest->vertex];
        graph->adjLists[dest->vertex] = newNode2;
    }
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
    int n, edges;
    scanf("%d ",&n);
    edges = n-1;
    struct Graph* graph = createGraph(n+1);
    struct node* vertices[n+1];
    for(int i=0;i<=n;i++) vertices[i] = 0;
    int weights[n];
    for(int i=0;i<n;i++) scanf("%d",&weights[i]);
    while(edges--)
    {
        int start, end;
        scanf("%d %d",&start,&end);
        start--;
        end--;
        if(!vertices[start]) vertices[start] = createNode(start, weights[start]);
        if(!vertices[end]) vertices[end] = createNode(end, weights[end]);
        addEdge(graph, vertices[start], vertices[end], vertices);
    }
    int start = 0;
    vertices[start]->parent = vertices[start];
    DFS(graph, vertices[start], vertices);
    for(int i=0;i<n;i++)
    {
        printf("%d ",vertices[i]->sumWeight);
    }
    printf("\n");
    int total = vertices[start]->sumWeight;
    int minWeights[n];
    for(int i=0;i<n;i++)
    {
        int num1 = vertices[i]->sumWeight;
        int num2 = total - num1;
        if(num1<num2) minWeights[i] = num1;
        else minWeights[i] = num2;
    }
    int max = -INF;
    int end;
    for(int i=0;i<n;i++)
    {
        if(minWeights[i]>max) 
        {
            max = minWeights[i];
            start = i;
            end = vertices[i]->parent->vertex;
        }
    }
    printf("%d\n",max);
    printf("delete edge between %d and %d\n",start+1,end+1);
    return 0;
}
