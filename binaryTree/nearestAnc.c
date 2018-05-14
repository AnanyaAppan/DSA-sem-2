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


int push(node* arr[],node* n,int *top)
{
    if(*top == N)
    {
        printf("stack full\n");
        return 0;
    }
    arr[++(*top)] = n;
    return 0;
}

node* pop(node* arr[],int *top)
{
    if(*top == -1)
    {
        printf("stack empty\n");
        return 0;
    }
    node* num = arr[(*top)--];
    return num;
}

int search(struct node* root, struct node* A)
{
    if(root->data == A->data) return 1;
    if(root->leftChild)
        if(search(root->leftChild,A)) return 1;
    if(root->rightChild)
        if(search(root->rightChild,A)) return 1;
    return 0;
}

struct node* nearestAnc(node* root, node* A, node* B)
{
    printf("%d %d %d\n",root->data,A->data, B->data);
    if(root==0) return 0;
    if(A->data == root->data) if(search(A,B)) return A;
    if(B->data == root->data) if(search(B,A)) return B;
    if(root->leftChild)
    {
        struct node* left = nearestAnc(root->leftChild,A,B);
        if(left) return left;
    }
    if(root->rightChild)
    {
        struct node* right = nearestAnc(root->rightChild,A,B);
        if(right) return right;
    }
    if(search(root,A) && search(root,B)) return root;
    return 0;
k
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
    addChild(&E,&H,8,0);
    addChild(&D,&G,5,1);
    printf("%d\n",nearestAnc(A, C, H)->data);
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