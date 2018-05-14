#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40

struct node
{
    int vertex;
    struct node* next;
    struct node* parent;
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

void bfs(struct Graph* graph, struct node* startVertex, struct node* vertices[])
{
    struct queue* q = createQueue();
    printf("%d\n",startVertex->vertex);
    graph->color[startVertex->vertex] = "yellow"; 
    enqueue(q, startVertex);
    
    while(!isEmpty(q)){
        //printQueue(q);
        struct node* currentVertex = dequeue(q);
        graph->color[currentVertex->vertex] = "blue";
        
        struct node* temp = graph->adjLists[currentVertex->vertex];
    
        while(temp) {
            if(!strcmp(graph->color[temp->vertex],"red")){
                printf("%d\n",temp->vertex);
                graph->color[temp->vertex] = "yellow";
                enqueue(q, temp);
                vertices[temp->vertex]->parent = currentVertex;
            }
            temp = temp->next;
        }
    }
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
        addEdge(graph, vertices[start], vertices[end], 0);
    }
    printf("enter start node\n");
    int start;
    scanf("%d",&start);
    start--;
    vertices[start]->parent = 0;
    printf("bfs traversal...\n");
    bfs(graph, vertices[start], vertices);
    return 0;
}
