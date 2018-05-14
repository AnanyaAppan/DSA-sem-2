//not working :p
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
    int p;
};

struct Graph
{
    int numVertices;
    int** parent;
    int** weightLists;
    int** d;
};

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    graph->parent = malloc(vertices * sizeof(struct node*));
    int i;
    for (i = 0; i < vertices; i++) {
        graph->parent[i] = malloc(vertices*sizeof(struct node));
    }

    graph->weightLists = (int**)malloc(vertices*sizeof(int*));

    for (i = 0; i < vertices; i++) {
        graph->weightLists[i] = (int*)malloc(vertices*sizeof(int));
    }
        
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    graph->weightLists[src][dest] = weight;
}

int APSP(struct Graph* graph)
{
    int num = graph->numVertices;
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
            for(int k=0;k<num;k++)
            {
                if(graph->weightLists[i][j] > graph->weightLists[i][k] + graph->weightLists[k][j])
                {
                    graph->weightLists[i][j] = graph->weightLists[i][k] + graph->weightLists[k][j];
                    graph->parent[i][j] = k; 
                }
            }
        }
    }
    return 0;
}

int printPath(struct Graph* graph, int i, int j)
{
    if(graph->parent[i][j]!=i)
    {
        printPath(graph,i,graph->parent[i][j]);
        printPath(graph,graph->parent[i][j],j);
    }
    else{
        printf("%d to %d\n",i+1,j+1);
    }
    return 0;
}

int main()
{
    printf("enter num of nodes\n");
    int n;
    scanf("%d",&n);
    struct Graph* graph = createGraph(n+1);
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
        addEdge(graph, start, end, weight);
        printf("edge added\n");
    }
    printf("enter start node\n");
    int start;
    scanf("%d",&start);
    start--;
    APSP(graph);
    printf("enter the node u want to go to\n");
    int dest;
    scanf("%d",&dest);
    dest--;
    printf("the path to be taken is...\n");
    printPath(graph, start, dest);
    return 0;
}