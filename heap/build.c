#include<stdio.h>
#include<stdlib.h>

int swap(int arr[],int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return 0;
}

int bottomUpHeapify(int i,int heap[])
{
    int p = (i-1)/2;
    while(i>0 && heap[i]<heap[p])
    {
        swap(heap,i,p);
        i = p;
        p = (i-1)/2;
    }
    return 0;
}

int topDownHeapify(int i,int heap[],int n)
{
    //printf("%d\n",n);
    int l = 2*i + 1;
    int r = 2*i + 2;
    int min;
    while(r<n)
    {
        if(heap[l]<heap[r]) min = l;
        else min = r;
        if(heap[i]>heap[min]){
            swap(heap,i,min);
            i = min;
            l = 2*i + 1;
            r = 2*i + 2;
        }
        else break;
    }
    if(l<n && heap[i]>heap[l])
    {
        swap(heap,i,l);
    }
    return 0;
}

int buildHeap(int arr[],int n)
{
    int i = n/2;
    while(i>=0)
    {
        topDownHeapify(i--,arr,n);
    }
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
    buildHeap(arr,n);
    printf("the array in the form of a heap\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}