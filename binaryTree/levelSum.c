#include<stdio.h>
#include<stdlib.h>
#define N 10000

typedef struct node{
    struct node* parent;
    struct node* leftChild;
    struct node* rightChild;
    int data;
} node;

int addChild(node** parent,node** child,int data,int left)
{
    (*child)->leftChild = NULL;
    (*child)->rightChild = NULL;
    (*child)->data = data;
    if(left) (*parent)->leftChild = *child;
    else  (*parent)->rightChild = *child;
    return 0;
}


int enqueue(node* queue[],node* num,int* front,int* end)
{
    if(*end==N)
    {
        printf("queue full!!\n");
        return 0;
    }
    if(*front==-1)
    {
        *front=0;
    }
    queue[++(*end)]=num;
    return 0;
}

node* dequeue(node* queue[],int* front,int* end)
{
    if(*front==-1)
    {
        printf("queue empty!!\n");
        return 0;
    }
    node* num = queue[*front];
    if(*front==*end)
    {
        *front = -1;
        *end = -1;
    }
    else
    {
        (*front)++;
    }
    return num;
}

int levelSum(node* root)
{
    node* queue[10000];
    int front = -1, rear = -1;
    enqueue(queue,root,&front,&rear);
    int num = 1;
    int i = 0;
    int sum;
    while(front!=-1)
    {
        i++;
        sum = 0;
        int numSub = 0;
        while(num--)
        {
            node* node = queue[front];
            if(node->leftChild != NULL) 
            {
                enqueue(queue, node->leftChild, &front, &rear);
                numSub++;
            }
            if(node->rightChild != NULL) 
            {
                enqueue(queue, node->rightChild, &front, &rear);
                numSub++;
            }
            sum += (dequeue(queue, &front, &rear))->data;
        }
        num = numSub;
        printf("sum of level %d = %d\n",i,sum);
    }
    printf("\n");
    return 0;
}

int main()
{
    node* A = (node*)malloc(1*sizeof(node));
    A->parent = NULL;
    A->leftChild = NULL;
    A->rightChild = NULL;
    A->data = 1;
    node* B = (node*)malloc(1*sizeof(node));
    node* C = (node*)malloc(1*sizeof(node));
    node* D = (node*)malloc(1*sizeof(node));
    node* E = (node*)malloc(1*sizeof(node));
    node* F = (node*)malloc(1*sizeof(node));
    node* G = (node*)malloc(1*sizeof(node));
    node* H = (node*)malloc(1*sizeof(node));
    addChild(&A,&B,3,1);
    addChild(&A,&C,4,0);
    addChild(&B,&D,9,0);
    addChild(&C,&E,7,1);
    addChild(&C,&F,0,0);
    addChild(&E,&H,3,0);
    addChild(&D,&G,4,1);
    levelSum(A);
    free(A);
    free(B);
    free(C);
    free(D);
    free(E);
    free(F);
    free(G);
    free(H);
    return 0;
}