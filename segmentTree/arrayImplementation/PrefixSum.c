#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define INF 1000000
int p = 0;

typedef struct node{
    struct node* parent;
    struct node* leftChild;
    struct node* rightChild;
    int data;
} node;

int getSum(int* BT, int i)
{
    int sum = 0;
    i++;
    while (i>0)
    {
        sum += BT[i];
        i -= i& (-i);
    }
    return sum;
}

int updateBT(int* BT, int n, int i, int val)
{
    i++;
    while (i <= n)
    {
       BT[i] += val;
       i += i & (-i);
    }
    return 0;
}

int* genBT(int* arr,int n)
{
    int height = ceil(log(n)/log(2));
    int* BT = (int*)malloc(sizeof(int)*2*pow(2,height));
    for(int i = 0;i<n;i++) updateBT(BT,n,i,arr[i]);
    return BT;
}

int main()
{
    int n;
    scanf("%d",&n);
    int* arr = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    int* BT = (int*)malloc(10000*sizeof(int));
    BT  = genBT(arr,n);
    printf("enter position\n");
    int pos;
    scanf("%d",&pos);
    printf("prefixSum = %d\n",getSum(BT,pos));
    free(arr);
    free(BT);
    return 0;
}