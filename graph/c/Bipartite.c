#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40

struct node
{
    int vertex;
    struct node* next;
    struct node* parent;
    int bipartColor;
};

struct queue {
    struct node* items[SIZE];
    int front;
    int rear;
};

int isEmpty(struct queue* q) {
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void enqueue(struct queue* q, struct node* value){
    if(q->rear == SIZE-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

struct node* dequeue(struct queue* q){
    struct node* item;
    if(isEmpty(q)){
        printf("Queue is empty");
        item = 0;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            //printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    newNode->bipartColor = 0;
    return newNode;
}
 
struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int** weightLists;
    char** color;
    int* bipartColor; 
};

void printQueue(struct queue *q) {
    int i = q->front;

    if(isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]->vertex);
        }
    }    
}

int bipartite(struct Graph* graph, struct node* startVertex, struct node* vertices[])
{
    struct queue* q = createQueue();
    printf("%d\n",startVertex->vertex);
    graph->color[startVertex->vertex] = "yellow"; 
    enqueue(q, startVertex);
    vertices[startVertex->vertex]->bipartColor = 1;
    int color;
    while(!isEmpty(q)){
        //printQueue(q);
        struct node* currentVertex = dequeue(q);
        graph->color[currentVertex->vertex] = "blue";
        if(vertices[currentVertex->vertex]->bipartColor==2) color = 1;
        else color = 2;
        struct node* temp = graph->adjLists[currentVertex->vertex];
    
        while(temp) {
            if(vertices[temp->vertex]->bipartColor==0) vertices[temp->vertex]->bipartColor = color;
            else if(vertices[temp->vertex]->bipartColor != color) return 0;
            if(!strcmp(graph->color[temp->vertex],"red")){
                printf("%d\n",temp->vertex);
                graph->color[temp->vertex] = "yellow";
                enqueue(q, temp);
                vertices[temp->vertex]->parent = currentVertex;
            }
            temp = temp->next;
        }
    }
    return 1;
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
    printf("bfs traversal...\n");
    if(bipartite(graph, vertices[start], vertices)) printf("bipartite\n");
    else printf("not bipartite\n");
    for(int i=0;i<n;i++) printf("%d color = %d\n",i,vertices[i]->bipartColor);
    return 0;
}