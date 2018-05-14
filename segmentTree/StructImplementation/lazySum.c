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
    return x+y;
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
        ST[i]->key = ST[left]->key + ST[right]->key;
    }
    return 0;
}

int rangeUpdate(struct node** ST, int l, int r,int leftCurr, int rightCurr,int i, int val, int choice)
{
    int len =( rightCurr - leftCurr + 1 )/2;
    printf("ST[%d] = %d\n",i,ST[i]->key);
    if(ST[i]->lazyBit==1)
    {
        printf("ST[%d]->lazyVal = %d\n",i,ST[i]->lazyVal);
        if(ST[i]->left < 2*N-1)
        {
            ST[ST[i]->left]->lazyBit = 1;
            ST[ST[i]->left]->lazyVal = f(ST[i]->lazyVal,ST[ST[i]->left]->lazyVal);
            ST[ST[i]->left]->key = (ST[ST[i]->left]->lazyVal)*(rightCurr-len-leftCurr + 1);
        }
        if(ST[i]->right < 2*N-1)
        {
            ST[ST[i]->right]->lazyBit = 1;
            ST[ST[i]->right]->lazyVal = f(ST[i]->lazyVal, ST[ST[i]->right]->lazyVal);
            ST[ST[i]->right]->key = (ST[ST[i]->right]->lazyVal)*(rightCurr-leftCurr-len + 1);  
        }
        ST[i]->lazyBit = 0;
        ST[i]->lazyVal = 0;
    }
    if(l==leftCurr && r==rightCurr) 
    {
        if(choice==1)
        {
            if(ST[i]->left<2*N-1)
            {
                ST[ST[i]->left]->lazyBit = 1;
                ST[ST[i]->left]->lazyVal = f(ST[i]->lazyVal,ST[ST[i]->left]->lazyVal);
                ST[ST[i]->left]->key += (ST[ST[i]->left]->lazyVal)*(rightCurr-len-leftCurr + 1);
            } 
            if(ST[i]->right<2*N-1)
            {
                ST[ST[i]->right]->lazyBit = 1;
                ST[ST[i]->right]->lazyVal = f(ST[i]->lazyVal, ST[ST[i]->right]->lazyVal);
                ST[ST[i]->right]->key += (ST[ST[i]->right]->lazyVal)*(rightCurr-leftCurr-len + 1);  
            }
            ST[i]->key += val*(rightCurr - leftCurr + 1);
            ST[i]->lazyBit = 0;
            ST[i]->lazyVal = 0;
        }
        return ST[i]->key;
    }
    if(l>=leftCurr+len) 
    {
        int num = rangeUpdate(ST,l,r,leftCurr+len,rightCurr,2*i+2,val, choice);
        if(choice==1)
        {
            ST[i]->key = num + ST[ST[i]->left]->key;
        }
        return num;
    }
    if(r<=rightCurr-len) 
    {
        int num = rangeUpdate(ST,l,r,leftCurr,rightCurr-len,2*i+1,val,choice);
        if(choice==1)
        {
            ST[i]->key = num + ST[ST[i]->right]->key; 
        }
        return num;
    }
    int num1 = rangeUpdate(ST,l,rightCurr-len,leftCurr,rightCurr-len,2*i+1,val,choice);
    int num2 = rangeUpdate(ST,leftCurr+len,r,leftCurr+len,rightCurr,2*i+2, val,choice);
    printf("num1 = %d num2 = %d\n",num1,num2);
    ST[i]->key = num1 + num2;
    return ST[i]->key;
}

int main()
{
    int n;
    scanf("%d",&n);
    int height = ceil(log(n)/log(2));
    int l,r;
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
            printf("sum of this range = %d\n",rangeUpdate(ST,l,r,0,N-1,0,0,choice));
        }
        printf("enter 1 to end\n");
        scanf("%d",&end);
    }
    free(arr);
    for(int i=0;i<10000;i++) free(ST[i]);
    free(ST);
    return 0;
}