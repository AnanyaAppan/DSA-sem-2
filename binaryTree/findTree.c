#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node* parent;
    struct node* leftChild;
    struct node* rightChild;
    int data;
} node;


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

int levelOrderTraversal(node* root)
{
    node* queue[10000];
    int front = -1, rear = -1;
    enqueue(queue,root,&front,&rear);
    while(front>-1)
    {
        root = queue[front];
        if(root->leftChild!=NULL)
            enqueue(queue,root->leftChild,&front,&rear);
        if(root->rightChild!=NULL)
            enqueue(queue,root->rightChild,&front,&rear);
        printf("%d ",root->data);
        dequeue(queue,&front,&rear);
    }
    printf("\n");
    return 0;
}

int addChild(node** parent,node** child,int data,int left)
{
    (*child)->leftChild = NULL;
    (*child)->rightChild = NULL;
    (*child)->data = data;
    if(left) (*parent)->leftChild = *child;
    else  (*parent)->rightChild = *child;
    return 0;
}

int findTree(node* root, int* preOrder, int* inOrder, int inStart, int preStart, int preEnd)
{
    int num = preOrder[preStart];
    root->data = num;
    for(int i=preStart;i<=preEnd;i++)
    {
        if(inOrder[i]==num) 
    }
    
    findTree(root->leftChild);
}


int main()
{
    int* inOrder = (int*)malloc(100*sizeof(int));
    int* preOrder = (int*)malloc(100*sizeof(int));
    printf("enter n\n");
    int n;
    scanf("%d",&n);
    printf("enter in order\n");
    for(int i=0;i<n;i++) scanf("%d",&inOrder[i]);
    printf("enter post order\n");
    for(int i=0;i<n;i++) scanf("%d",&preOrder[i]);
    node* A = (node*)malloc(1*sizeof(node));
    A->parent = NULL;
    A->leftChild = NULL;
    A->rightChild = NULL;
    findTree(A,preOrder,inOrder,0,0,n-1);
    free(inOrder);
    free(preOrder);
}