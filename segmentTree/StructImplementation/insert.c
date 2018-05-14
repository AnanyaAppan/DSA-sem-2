
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define INF 1000000

typedef struct node{
    int left;
    int right;
    int key;
} node;

int f(int x, int y)
{
    return x<=y;
}

struct node* newNode(struct node* node, int key, int pos)
{
    node->key   = key;
    node->left   = 2*pos + 1;
    node->right  = 2*pos + 2;
    return(node);
}

int update(struct node** ST, int i, int val, int h)
{
    int curr = pow(2,h)-1+i;
    // printf("curr = %d\n",curr);
    ST[curr]->key = val;
    int p = (curr-1)/2;
    while(p>0)
    {
        int leftChild = 2*p +1;
        int rightChild = 2*p +2;
        if(f(ST[leftChild]->key,ST[rightChild]->key)) ST[p]->key = ST[leftChild]->key;
        else ST[p]->key = ST[rightChild]->key;
        p = (p-1)/2;
    }
    int leftChild = 2*p +1;
    int rightChild = 2*p +2;
    if(f(ST[leftChild]->key,ST[rightChild]->key)) ST[p]->key = ST[leftChild]->key;
    else ST[p]->key = ST[rightChild]->key;
    p = (p-1)/2;
    // for(int i=0;i<2*pow(2,h);i++) printf("%d ",ST[i]);
    return 0;
}

int genST(struct node** ST,int* arr,int n)
{
    int height = ceil(log(n)/log(2));
    int i,j;
    for(i = pow(2,height)-1,j=0;j<n;i++,j++)
    {
        ST[i] = newNode(ST[i],arr[j],i);
    }
    for(i;i<pow(2,height+1)-1;i++)
    {
        ST[i] = newNode(ST[i],INF,i);
    }
    for(int i = pow(2,height)-2; i>=0 ; i--)
    {
        int left = 2*i+1;
        int right =  2*i + 2;
        if(f(ST[left]->key,ST[right]->key)) ST[i]->key = ST[left]->key;
        else ST[i]->key = ST[right]->key;
    }
    return 0;
}

int RMQ(struct node** ST,int l,int r, int leftCurr, int rightCurr, int i)
{
    int len =( rightCurr - leftCurr + 1 )/2;
    if(l==leftCurr && r==rightCurr) return ST[i]->key;
    if(l>=leftCurr+len) return RMQ(ST,l,r,leftCurr+len,rightCurr,2*i+2);
    if(r<=rightCurr-len) return RMQ(ST,l,r,leftCurr,rightCurr-len,2*i+1);
    int min1 = RMQ(ST,l,rightCurr-len,leftCurr,rightCurr-len,2*i+1);
    int min2 = RMQ(ST,leftCurr+len,r,leftCurr+len,rightCurr,2*i+2);
    if(min1<min2) return min1;
    return min2;
}

int main()
{
    int n;
    scanf("%d",&n);
    int height = ceil(log(n)/log(2));
    int l,r;
    scanf("%d %d",&l,&r);
    int* arr = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    struct node** ST = (struct node**)malloc(10000*sizeof(struct node*));
    for(int i=0;i<10000;i++) ST[i] = (struct node*)malloc(sizeof(struct node));
    genST(ST,arr,n);
    int N = pow(2,height);
    printf("min = %d\n",RMQ(ST,l,r,0,N-1,0));
    printf("enter num to update and position\n");
    int num, pos;
    scanf("%d %d",&num,&pos);
    update(ST, pos, num,height);
    printf("enter l and r\n");
    scanf("%d %d",&l,&r); 
    printf("min = %d\n",RMQ(ST,l,r,0,N-1,0)); 
    free(arr);
    for(int i=0;i<10000;i++) free(ST[i]);
    free(ST);
    return 0;
}