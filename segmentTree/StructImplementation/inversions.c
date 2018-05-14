
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define INF 1000000

typedef struct node{
    int left;
    int right;
    int key;
    int* subArr;
    int inversionCount;
    int height;
} node;

int max(int a,int b)
{
    if(a>b) return a;
    return b;
}

int f(int x, int y)
{
    return x<=y;
}

struct node* genArray(struct node* node, struct node** ST)
{
    if(node->left && node->right)
    {
        int size = pow(2,node->height-1);
        node->subArr = (int*)realloc(node->subArr,size*sizeof(int));
        int* arr1 = ST[node->left]->subArr;
        int* arr2 = ST[node->right]->subArr;
        int count=0;
        int left = 0, right = 0;
        int p = 0;
        while(left<size && right<size)
        {
            if(arr1[left]<=arr2[right] && left<size)
            {
                node->subArr[p++] = arr1[left++];
            }
            else if(right<size)
            {
                count += size-left;
                node->subArr[p++] = arr2[right++];  
            }
        }
        while(left<size)
        {
            node->subArr[p++] = arr1[left++];
        } 
        while(right<size)
        {
            node->subArr[p++] = arr2[right++];
        }
        node->inversionCount = count + ST[node->left]->inversionCount + ST[node->right]->inversionCount;
    }
    return node;
}

struct node* newNode(struct node* node, int key, int pos)
{
    node->height = 0;
    node->key   = key;
    node->left   = 2*pos + 1;
    node->right  = 2*pos + 2;
    node->subArr = (int*)malloc(sizeof(int));
    node->subArr[0] = key;
    node->inversionCount = 0;
    return(node);
}

struct node* updateHeight(struct node* node, struct node** ST)
{
    if(ST[node->right] && ST[node->left]) node->height = max(ST[node->left]->height , ST[node->right]->height) + 1;
    else if(ST[node->left]) node->height = ST[node->left]->height + 1;
    else if(ST[node->right]) node->height = ST[node->right]->height + 1;
    else node->height = 0;
    //printf("height = %d\n",node->height);
    return node;

}

int update(struct node** ST, int i, int val, int h)
{
    int curr = pow(2,h)-1+i;
    ST[curr]->key = val;
    int p = (curr-1)/2;
    while(p>0)
    {
        int leftChild = 2*p +1;
        int rightChild = 2*p +2;
        if(f(ST[leftChild]->key,ST[rightChild]->key)) ST[p]->key = ST[leftChild]->key;
        else ST[i]->key = ST[rightChild]->key;
        p = (p-1)/2;
    }
    int leftChild = 2*p +1;
    int rightChild = 2*p +2;
    if(f(ST[leftChild]->key,ST[rightChild]->key)) ST[p]->key = ST[leftChild]->key;
    else ST[i]->key = ST[rightChild]->key;
    p = (p-1)/2;
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
        ST[i] = newNode(ST[i],0,i);
        ST[i] = updateHeight(ST[i],ST);
        ST[i] = genArray(ST[i], ST);
    }
    return 0;
}

int numInversions(struct node** ST,int l,int r, int leftCurr, int rightCurr, int i)
{
    printf("%d %d\n",leftCurr,rightCurr);
    int len =( rightCurr - leftCurr + 1 )/2;
    if(l==leftCurr && r==rightCurr) return ST[i]->inversionCount;
    if(l>=leftCurr+len) return numInversions(ST,l,r,leftCurr+len,rightCurr,2*i+2);
    if(r<=rightCurr-len) return numInversions(ST,l,r,leftCurr,rightCurr-len,2*i+1);
    int num1 = numInversions(ST,l,rightCurr-len,leftCurr,rightCurr-len,2*i+1);
    int num2 = numInversions(ST,leftCurr+len+1,r,leftCurr+len+1,rightCurr,2*i+2);
    int size = pow(2,ST[i]->height-1);
    int* arr1 = ST[ST[i]->left]->subArr;
    int* arr2 = ST[ST[i]->right]->subArr;
    int count = 0;
    int left = 0, right = 0;
    while(left<size && right<size)
    {
        if(arr1[left]<=arr2[right] && left<size)
        {
            left++;
        }
        else if(right<size)
        {
            count += size-left;
            right++; 
        }
    }
    return num1 + num2 + count;
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
    printf("number of inversions = %d\n",numInversions(ST,l,r,0,n-1,0)); 
    free(arr);
    for(int i=0;i<10000;i++) free(ST[i]);
    free(ST);
    return 0;
}