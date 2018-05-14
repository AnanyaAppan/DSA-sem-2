#include<stdio.h>
#include<stdlib.h>
#include"./../del.c"

int merge(int arr[],int i, int k, int j)
{
    int left = i, right = k+1;
    int B[100];
    int p=i;
    while(left<k+1 && right<j+1)
    {
        if(arr[left]<arr[right])
        {
            B[p++] = arr[left++];
        }
        else
        {
            B[p++] = arr[right++];  
        }
    }
    while(left<=k)
    {
        B[p++] = arr[left++];
    } 
    while(right<=j)
    {
        B[p++] = arr[right++];
    }
    for(int n=i;n<=j;n++) arr[n] = B[n];
    return 0;
}

int mergeSort(int arr[],int i,int j)
{
    if(i==j) return 0;
    int k = (i+j)/2;
    mergeSort(arr,i,k);
    mergeSort(arr,k+1,j);
    merge(arr,i,k,j);
    return 0;
}

struct node* buildTree(struct node* node, int* arr, int i, int j)
{
    if(i>j) return 0;
    int mid = (i+j)/2;
    if(node==0) node = insert(node, arr[mid],0);
    else insert(node, arr[mid],0);
    buildTree(node,arr,i,mid-1);
    buildTree(node,arr,mid+1, j);
    return node;
}

int main()
{
    int n;
    printf("enter number of elements\n");
    scanf("%d",&n);
    printf("enter array\n");
    int arr[n];
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    mergeSort(arr,0,n-1);
    struct node *root = NULL;
    root = buildTree(root, arr, 0, n-1);
    inorder(root);
    return 0;
}