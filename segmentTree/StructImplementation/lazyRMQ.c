#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define INF 1000000
int N;

typedef struct node{
    int left;
    int right;
    int key;
    int lazyBit;
    int lazyVal;
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
    node->lazyBit = 0;
    node->lazyVal = 0;
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

int rangeUpdate(struct node** ST, int l, int r,int leftCurr, int rightCurr,int i, int val, int choice)
{
    printf("ST[%d] = %d\n",i,ST[i]->key);
    if(ST[i]->lazyBit==1)
    {
        printf("ST[%d]->lazyVal = %d\n",i,ST[i]->lazyVal);
        if(ST[i]->left < 2*N-1)
        {
            ST[ST[i]->left]->lazyBit = 1;
            ST[ST[i]->left]->lazyVal = ST[i]->lazyVal;
            ST[ST[i]->left]->key = ST[i]->lazyVal;
        }
        if(ST[i]->right < 2*N-1)
        {
            ST[ST[i]->right]->lazyBit = 1;
            ST[ST[i]->right]->lazyVal = ST[i]->lazyVal;
            ST[ST[i]->right]->key = ST[i]->lazyVal;  
        }
        ST[i]->lazyBit = 0;
    }
    int len =( rightCurr - leftCurr + 1 )/2;
    if(l==leftCurr && r==rightCurr) 
    {
        if(choice==1)
        {
            if(ST[i]->left<2*N-1)
            {
                ST[ST[i]->left]->lazyBit = 1;
                ST[ST[i]->left]->lazyVal = val;
                ST[ST[i]->left]->key = val;
            } 
            if(ST[i]->right<2*N-1)
            {
                ST[ST[i]->right]->lazyBit = 1;
                ST[ST[i]->right]->lazyVal = val;
                ST[ST[i]->right]->key = val;
            }
            ST[i]->key = val;
        }
        ST[i]->lazyBit = 0;
        return ST[i]->key;
    }
    if(l>=leftCurr+len) 
    {
        int num = rangeUpdate(ST,l,r,leftCurr+len,rightCurr,2*i+2,val, choice);
        if(choice==1)
        {
            if(f(val, ST[ST[i]->left]->key)) ST[i]->key = num;
            else ST[i]->key = ST[ST[i]->left]->key;
        }
        return num;
    }
    if(r<=rightCurr-len) 
    {
        int num = rangeUpdate(ST,l,r,leftCurr,rightCurr-len,2*i+1,val,choice);
        if(choice==1)
        {
            if(f(val, ST[ST[i]->right]->key)) ST[i]->key = num;
            else ST[i]->key = ST[ST[i]->right]->key;
        }
        return num;
    }
    int min1 = rangeUpdate(ST,l,rightCurr-len,leftCurr,rightCurr-len,2*i+1,val,choice);
    int min2 = rangeUpdate(ST,leftCurr+len,r,leftCurr+len,rightCurr,2*i+2, val,choice);
    printf("min1 = %d min2 = %d\n",min1,min2);
    if(min1<min2) 
    {
        ST[i]->key = min1;
        return min1;
    }
    ST[i]->key = min2;
    return min2;
}

int main()
{
    int n;
    scanf("%d",&n);
    int height = ceil(log(n)/log(2));
    int l,r;
    // scanf("%d %d",&l,&r);
    int* arr = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    struct node** ST = (struct node**)malloc(10000*sizeof(struct node*));
    for(int i=0;i<10000;i++) ST[i] = (struct node*)malloc(sizeof(struct node));
    genST(ST,arr,n);
    N = pow(2,height);
    int num, pos;
    printf("time for range updates!!\n");
    int end = 0;
    while(!end)
    {
        printf("enter range\n");
        scanf("%d %d",&l,&r);
        int choice;
        printf("enter 1 to update, 2 to query\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            int num;
            scanf("%d",&num);
            rangeUpdate(ST,l,r,0,N-1,0,num, choice) ;
            printf("updated!!\n");
        }
        if(choice==2)
        {
            printf("minimum in this range = %d\n",rangeUpdate(ST,l,r,0,N-1,0,0,choice));
        }
        printf("enter 1 to end\n");
        scanf("%d",&end);
    }
    free(arr);
    for(int i=0;i<10000;i++) free(ST[i]);
    free(ST);
    return 0;
}