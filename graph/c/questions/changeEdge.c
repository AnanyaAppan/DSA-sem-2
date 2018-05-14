#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 1000000
int t = 1;
int edgeIndex=0;
 
struct node
{
    int vertex;
    int d;
    int f;
    int color;
    struct node* next;
    struct node* parent;
};

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

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    newNode->color = 0;
    return newNode;
}

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int** weightLists;
    char** color; 
    int numEdges;
    int* C;
    int* S;
    int** L;
    struct Edge** edges; 
};

int delEdge(struct Graph* graph,int start, int end)
{
    struct node* temp = graph->adjLists[start];
    if(temp->vertex==end)
    {
        graph->adjLists[start] = temp->next;
        free(temp);
        return 0;
    }
    while(temp->next)
    {
        if(temp->next->vertex == end)
        {
            break;
        }
        temp = temp->next;
    }
    temp->next = temp->next->next;
    free(temp->next);
    return 0;
}


int DFS(struct Graph* graph, struct node* vertex, struct node* vertices[], int color) {
    struct node* temp = graph->adjLists[vertex->vertex];
    vertices[vertex->vertex]->color = color;
    graph->color[vertex->vertex] = "yellow";
    vertices[vertex->vertex]->d = t++;

    while(temp!=NULL) {
        if(!strcmp(graph->color[temp->vertex],"red")){
            temp->parent = vertices[vertex->vertex];
            DFS(graph, temp, vertices,color);
            graph->color[temp->vertex] = "blue";
            vertices[temp->vertex]->color = color;
        }
        temp = temp->next;
    } 
    vertices[vertex->vertex]->f = t++;
    return 0;     
}


struct Graph* createGraph(int vertices, int edges)
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
    graph->numEdges = edges;
    
    graph->C = (int*)malloc(vertices*sizeof(int));
    for(int i=0;i<vertices;i++) graph->C[i] = i;

    graph->S = (int*)malloc(vertices*sizeof(int));
    for(int i=0;i<vertices;i++) graph->S[i] = 1;

    graph->L = (int**)malloc(vertices*sizeof(int*));
    for(int i=0;i<vertices;i++)
    {
        graph->L[i] = malloc(vertices*sizeof(int));
        for(int j=0;j<vertices;j++)
        {
            graph->L[i][j] = 0;
        }
    }
    graph->edges = (struct Edge**)malloc(edges*sizeof(struct Edge*));

    return graph;
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

void addEdge(struct Graph* graph, struct node* src, struct node* dest, int weight)
{
    struct Edge* e = malloc(sizeof(struct Edge));
    e->start = src->vertex;
    e->end = dest->vertex;
    e->weight = weight;
    graph->edges[edgeIndex++] = e;
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
    graph->weightLists[src->vertex][dest->vertex] = weight;
    // Add edge from dest to src
    newNode = createNode(src->vertex);
    if(graph->adjLists[dest->vertex]==0)
    {
        graph->adjLists[dest->vertex] = newNode;
    }
    else{
        newNode->next = graph->adjLists[dest->vertex];
        graph->adjLists[dest->vertex] = newNode;
    }
    graph->weightLists[dest->vertex][src->vertex] = weight;
}


int DFS1(struct Graph* graph, struct node* vertex, struct node* vertices[],int end, int weight) {
    
    int* maxEdge = (int*)malloc(2*sizeof(int));
    int max = -INF;
    int maxStart,maxEnd;

    struct node* temp = graph->adjLists[vertex->vertex];
    graph->color[vertex->vertex] = "yellow";
    vertices[vertex->vertex]->d = t++;

    while(temp!=NULL) {
        if(!strcmp(graph->color[temp->vertex],"red")){
            if(graph->weightLists[vertex->vertex][temp->vertex]>max)
            {
                max = graph->weightLists[vertex->vertex][temp->vertex];
                maxStart = vertex->vertex;
                maxEnd = temp->vertex;
                printf("start = %d end = %d max = %d\n",maxStart,maxEnd,max);
            }
            if(temp->vertex == end)
            {
                maxEdge[0] = maxStart;
                maxEdge[1] = maxEnd;
                printf("maxEdge = %d %d\n",maxStart,maxEnd);
                if(graph->weightLists[maxStart][maxEnd] > weight)
                {
                    vertices[maxEnd]->parent = 0;
                    delEdge(graph, maxStart, maxEnd);
                    return 1;
                }
                return 0;
            }
            temp->parent = vertices[vertex->vertex];
            DFS1(graph, temp, vertices, end, weight);
            graph->color[temp->vertex] = "blue";
        }
        temp = temp->next;
    } 
    vertices[vertex->vertex]->f = t++;
    return 0;     
}

struct Graph* Krushkals(struct Graph* graph, struct node* vertices[])
{
    struct Graph* MST = createGraph(graph->numVertices,graph->numEdges-1);
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
            addEdge(MST,vertices[e->start],vertices[e->end],graph->weightLists[e->start][e->end]);
            if(graph->S[color1] > graph->S[color2])
            {
                graph->C[e->end] = color1;
                for(int i=0;i<graph->numVertices;i++)
                {
                    if(graph->L[color2][i] != 0)
                    {
                        graph->L[color1][i] = 1;
                        graph->L[color2][i] = 0;
                        graph->C[i] = color1;
                    } 
                }
                graph->S[color1] += graph->S[color2];
                graph->S[color2] = 0;
            }
            else{
                graph->C[e->start] = color2;
                for(int i=0;i<graph->numVertices;i++)
                {
                    if(graph->L[color1][i] != 0)
                    {
                        graph->L[color2][i] = 1;
                        graph->L[color1][i] = 0;
                        graph->C[i] = color2;
                    } 
                }
                graph->S[color2] += graph->S[color1];
                graph->S[color1] = 0;
            }
        }
    }
    return MST;
}

int decreaseWeight(struct Graph* graph, struct Graph* MST, int start,int end, int weight,struct node* vertices[])
{
    graph->weightLists[start][end] = weight;
    graph->weightLists[end][start] = weight;
    if(DFS1(MST, vertices[start], vertices, end, weight)) 
    {
        addEdge(graph, vertices[start], vertices[end], weight);
        vertices[end]->parent = vertices[start];
    }
    for(int i=0;i<graph->numVertices-1;i++)
    {
        if(vertices[i]->parent != 0)
            printf("%d to %d\n",vertices[i]->vertex,vertices[i]->parent->vertex);
    }
    return 0;
}

int increaseWeight(struct Graph* graph,struct Graph* MST, int start, int end, int weight, struct node* vertices[])
{
    vertices[end]->parent = 0;
    int min = INF;
    int newStart, newEnd;
    graph->weightLists[start][end] = weight;
    graph->weightLists[end][start] = weight;
    MST->weightLists[start][end] = INF;
    MST->weightLists[end][start] = INF;
    delEdge(MST,start,end);
    delEdge(MST,end,start);
    DFS(MST,vertices[start],vertices,1);
    DFS(MST,vertices[end],vertices,2);
    for(int i=0;i<graph->numVertices;i++)
    {
        struct node* temp = graph->adjLists[i];
        while(temp)
        {
            if(vertices[i]->color != vertices[temp->vertex]->color)
            {
                if(graph->weightLists[i][temp->vertex] < min)
                {
                    min = graph->weightLists[i][temp->vertex];
                    newStart = i;
                    newEnd = temp->vertex;
                }
            }
            temp = temp->next;
        }
    }
    printf("new colors\n");
    for(int i=0;i<graph->numVertices;i++) 
    {
        if(vertices[i]!=0)
            printf("%d ",vertices[i]->color);
    }
    printf("\n");
    printf("replaced edge with start = %d end = %d\n",newStart,newEnd);
    vertices[newEnd]->parent = vertices[newStart];
    addEdge(MST,vertices[newStart],vertices[newEnd],min);
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
    int start, end, weight;
    while(edges--)
    {
        scanf("%d %d %d",&start,&end,&weight);
        start--;
        end--;
        if(!vertices[start]) vertices[start] = createNode(start);
        if(!vertices[end]) vertices[end] = createNode(end);
        addEdge(graph, vertices[start], vertices[end],weight);
    }
    struct Graph* MST = Krushkals(graph,vertices);
    // printf("enter edge start and end and new weight\n");
    // scanf("%d %d %d",&start,&end,&weight);
    // start--;
    // end--;
    // increaseWeight(graph,MST,start,end,weight,vertices);
    printf("enter edge start and end and new weight\n");
    scanf("%d %d %d",&start,&end,&weight);
    start--;
    end--;
    decreaseWeight(graph, MST, start, end, weight, vertices);
    return 0;
}