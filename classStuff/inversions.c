#include<stdio.h>
#include<stdlib.h>

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

int main()
{
    int n;
    scanf("%d",&n);
    int arr[100];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    mergeSort(arr,0,n-1);
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}