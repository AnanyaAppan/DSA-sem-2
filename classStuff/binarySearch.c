#include<stdio.h>
#include<stdlib.h>

int printArray(int arr[],int i,int j)
{
    for(int k=i;k<=j;k++) printf("%d ",arr[k]);
    printf("\n");
    return 0;
}

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

int binarySearch(int ele, int arr[], int n)
{
    mergeSort(arr,0,n-1);
    printArray(arr,0,n-1);
    int pos = -1;
    int beg = 0, end = n-1;
    int mid = (beg+end)/2;
    while(beg<=end)
    {
        if(arr[mid]==ele) return mid;
        else if(arr[mid]>ele) end = mid-1;
        else beg = mid+1;
        mid = (beg+end)/2;
    }
    return pos;
}

int main()
{
    printf("enter n\n");
    int n;
    scanf("%d",&n);
    printf("enter array elements\n");
    int arr[1000];
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    printf("enter element to search for\n");
    int ele;
    scanf("%d",&ele);
    int pos = binarySearch(ele,arr,n);
    if(pos!=-1) printf("found \n");
    else printf("not found\n");
    return 0;
}