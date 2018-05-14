
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define INF 1000000
int N;
int n;
int check = 0;

typedef struct node{
    int left;
    int right;
    int key;
    int minIndex;
    int max;
    int maxIndex;
} node;

int f(int x, int y)
{
    return x<=y;
}

struct node* newNode(struct node* node, int key, int pos)
{
    node->key   = key;
    node->max = key;
    node->left   = 2*pos + 1;
    node->right  = 2*pos + 2;
    node->minIndex = pos;
    node->maxIndex = pos;
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
        if(f(ST[leftChild]->key,ST[rightChild]->key)) 
        {
            ST[p]->key = ST[leftChild]->key;
            ST[p]->minIndex = ST[leftChild]->minIndex;
        }
        else 
        {
            ST[p]->key = ST[rightChild]->key;
            ST[p]->minIndex = ST[rightChild]->minIndex;
        }
        if(f(ST[leftChild]->max,ST[rightChild]->max))
        {
            ST[i]->max = ST[rightChild]->max;
            ST[i]->maxIndex = ST[rightChild]->maxIndex;
        }
        else{
            ST[i]->max = ST[leftChild]->max;
            ST[i]->maxIndex = ST[leftChild]->maxIndex;
        }
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
        if(f(ST[left]->key,ST[right]->key)) 
        {
            ST[i]->key = ST[left]->key;
            ST[i]->minIndex = ST[left]->minIndex;
        }
        else 
        {
            ST[i]->key = ST[right]->key;
            ST[i]->minIndex = ST[right]->minIndex;
        }
        if(f(ST[left]->max,ST[right]->max))
        {
            ST[i]->max = ST[right]->max;
            ST[i]->maxIndex = ST[right]->maxIndex;
        }
        else{
            ST[i]->max = ST[left]->max;
            ST[i]->maxIndex = ST[left]->maxIndex;
        }
    }
    return 0;
}

int MoveRight(struct node** ST,int l,int r, int leftCurr, int rightCurr, int i, int pos, int num)
{
    // printf("l = %d r = %d lc = %d rc = %d\n",l,r,leftCurr,rightCurr);
    if(ST[i])
    {
        if(leftCurr==rightCurr) 
        {
            if(ST[i]->key < num) return num;
            else return num + rightCurr - pos;
        }
    }
    else return num;
    if(l>N || r>N) return num;
    if(l>r) return num;
    int len =( rightCurr - leftCurr + 1 )/2;
    if(l==leftCurr && r==rightCurr) 
    {
        if(ST[i]->key > num) 
            return num + rightCurr - pos;
        else{
            if(ST[i]->minIndex-1 < rightCurr-len)
                return MoveRight(ST, l, ST[i]->minIndex-1,leftCurr,rightCurr-len,2*i+1, pos, num);
            else
            {
                int num1 =  MoveRight(ST,l, ST[i]->minIndex-1,leftCurr,rightCurr-len,2*i+1, pos, num);
                printf("num1 = %d\n",num1);
                if(num1==num) 
                    return num;
                int num2 =  MoveRight(ST,leftCurr+len, ST[i]->minIndex-1,leftCurr+len,rightCurr,2*i+2, pos, num);
                if(num2 != num && check==0)
                {
                    return num2;
                } 
                check = 1;
                return num1;
            }
        }
    }
    if(l>=leftCurr+len) return MoveRight(ST,l,r,leftCurr+len,rightCurr,2*i+2, pos, num);
    if(r<=rightCurr-len) return MoveRight(ST,l,r,leftCurr,rightCurr-len,2*i+1, pos, num);
    int num1 =  MoveRight(ST,l,rightCurr-len,leftCurr,rightCurr-len,2*i+1, pos, num);
    // printf("num1 = %d\n",num1);
    if(num1==num) 
        return num;
    int num2 =  MoveRight(ST,leftCurr+len,r,leftCurr+len,rightCurr,2*i+2, pos, num);
    if(num2 != num && check==0)
    {
        return num2;
    } 
    check = 1;
    return num1;
}

int MoveLeft(struct node** ST,int l,int r, int leftCurr, int rightCurr, int i, int pos, int num)
{
    if(ST[i]) 
    {
        if(leftCurr==rightCurr) 
        {
            if(ST[i]->max > num) return num;
            else return num - pos + leftCurr;
        }
    }
    else return num;
    if(l>N || r>N) return num;
    if(l>r) return num;
    int len =( rightCurr - leftCurr + 1 )/2;
    if(l==leftCurr && r==rightCurr) 
    {
        if(ST[i]->max < num) return num - pos + leftCurr;
        else{
            if(ST[i]->maxIndex+1 > leftCurr+len)
                return MoveLeft(ST,ST[i]->maxIndex+1,r,leftCurr+len,rightCurr,2*i+2, pos, num);
            else
            {
                int num1 = MoveLeft(ST,ST[i]->maxIndex+1,r,leftCurr,rightCurr-len,2*i+2, pos, num);
                if(num1==num) 
                    return num;
                int num2 =  MoveLeft(ST,ST[i]->maxIndex+1,r,leftCurr+len,rightCurr,2*i+1, pos, num); 
                if(num2 != num && check==0)
                {
                    return num2;
                } 
                check = 1;
                return num1;
            }
        }
    }
    if(l>=leftCurr+len) return MoveLeft(ST,l,r,leftCurr+len,rightCurr,2*i+2, pos, num);
    if(r<=rightCurr-len) return MoveLeft(ST,l,r,leftCurr,rightCurr-len,2*i+1, pos, num);
    int num1 = MoveLeft(ST,leftCurr+len,r,leftCurr,rightCurr-len,2*i+2, pos, num);
    if(num1==num) 
        return num;
    int num2 =  MoveLeft(ST,l,rightCurr-len,leftCurr+len,rightCurr,2*i+1, pos, num); 
    if(num2 != num && check==0)
    {
        return num2;
    } 
    check = 1;
    return num1;   
}

int printArray(int arr[], int n)
{
    for(int i = 0;i<n;i++) printf("%d ",arr[i]);
    printf("\n");
}

int main()
{
    printf("enter size of array\n");
    scanf("%d",&n);
    int height = ceil(log(n)/log(2));
    N = pow(2,height);
    int* arr = (int*)malloc(n*sizeof(int));
    printf("enter array\n");
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    struct node** ST = (struct node**)malloc((2*N-1)*sizeof(struct node*));
    for(int i=0;i<10000;i++) 
        ST[i] = (struct node*)malloc(sizeof(struct node));
    genST(ST,arr,n);
    // for(int i = 0;i<N; i++) printf("%d ",ST[i]->key);
    printf("\n");
    int stop = 0;
    while(!stop)
    {
        int pos;
        printf("enter position\n");
        scanf("%d",&pos);
        printf("enter 1 to move right and 2 to move left\n");
        int opt;
        scanf("%d",&opt);
        if(opt==1)
            arr[pos] = MoveRight(ST, pos + 1, n-1, 0 ,N-1, 0, pos, arr[pos]) + 1;
        if(opt==2)
            arr[pos] = MoveLeft(ST, 0, pos-1, 0 ,N-1, 0, pos, arr[pos]) - 1;
        update(ST, pos, arr[pos], height);
        check = 0;
        printf("new array \n");
        printArray(arr, n);
    }
    free(arr);
    for(int i=0;i<10000;i++) free(ST[i]);
    free(ST);
    return 0;
}