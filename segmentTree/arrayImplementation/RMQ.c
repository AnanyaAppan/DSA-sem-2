#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define INF 1000000

typedef struct node{
    struct node* parent;
    struct node* leftChild;
    struct node* rightChild;
    int data;
} node;

int f(int x, int y)
{
    return x<=y;
}

int update(int* ST, int i, int val, int h)
{
    int curr = pow(2,h)-1+i;
    // printf("curr = %d\n",curr);
    ST[curr] = val;
    int p = (curr-1)/2;
    while(p>0)
    {
        int leftChild = 2*p +1;
        int rightChild = 2*p +2;
        // printf("leftChildIndex = %d rci = %d\n",leftChild,rightChild);
        if(f(ST[leftChild],ST[rightChild])) ST[p] = ST[leftChild];
        else ST[i] = ST[rightChild];
        p = (p-1)/2;
    }
    int leftChild = 2*p +1;
    int rightChild = 2*p +2;
    if(f(ST[leftChild],ST[rightChild])) ST[p] = ST[leftChild];
    else ST[i] = ST[rightChild];
    p = (p-1)/2;
    // for(int i=0;i<2*pow(2,h);i++) printf("%d ",ST[i]);
    return 0;
}

int* genST(int* arr,int n)
{
    int height = ceil(log(n)/log(2));
    int* ST = (int*)malloc(sizeof(int)*2*pow(2,height));
    int i,j;
    for(i = pow(2,height)-1,j=0;j<n;i++,j++)
    {
        ST[i] = arr[j];
    }
    for(i;i<pow(2,height+1)-1;i++)
    {
        ST[i] = INF;
    }
    for(int i = pow(2,height)-2; i>=0 ; i--)
    {
        int leftChild = 2*i +1;
        int rightChild = 2*i +2;
        if(f(ST[leftChild],ST[rightChild])) ST[i] = ST[leftChild];
        else ST[i] = ST[rightChild];
    }
    // for(int i=0;i<2*pow(2,height)-1;i++) printf("%d ",ST[i]);
    // printf("\n");
    return ST;
}

int RMQ(int* ST,int l,int r, int leftCurr, int rightCurr, int i)
{
    int len =( rightCurr - leftCurr + 1 )/2;
    // printf("segment = %d, %d\n",leftCurr,rightCurr);
    // printf("i = %d\n",i);
    if(l==leftCurr && r==rightCurr) return ST[i];
    if(l>=leftCurr+len) return RMQ(ST,l,r,leftCurr+len,rightCurr,2*i+2);
    if(r<=rightCurr-len) return RMQ(ST,l,r,leftCurr,rightCurr-len,2*i+1);
    int min1 = RMQ(ST,l,rightCurr-len,leftCurr,rightCurr-len,2*i+1);
    int min2 = RMQ(ST,leftCurr+len+1,r,leftCurr+len+1,rightCurr,2*i+2);
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
    int* ST = (int*)malloc(10000*sizeof(int));
    ST  = genST(arr,n);
    int N = pow(2,height);
    printf("min = %d\n",RMQ(ST,l,r,0,N-1,0));
    printf("enter num to update and position\n");
    int num, pos;
    scanf("%d %d",&num,&pos);
    update(ST, pos, num,height);
    printf("enter l and r\n");
    scanf("%d %d",&l,&r); 
    printf("min = %d\n",RMQ(ST,l,r,0,n-1,0)); 
    free(arr);
    free(ST);
    return 0;
}
