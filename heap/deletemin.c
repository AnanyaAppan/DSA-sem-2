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

int delMin(int heap[],int* n)
{
    int min = heap[0];
    swap(heap,0,(*n)-1);
    *n -= 1;
    topDownHeapify(0,heap,n);
    return min;
}

int main()
{
    int heap[10000];
    int n = 0;
    printf("enter 1 to add, 0 to exit\n");
    int ans;
    scanf("%d",&ans);
    while(ans)
    {
        printf("enter the number to add to the heap\n");
        scanf("%d",&heap[n++]);
        bottomUpHeapify(n-1,heap);
        printf("enter 1 to add, 0 to exit\n");
        scanf("%d",&ans);
    }
    printf("the heap in level order is\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",heap[i]);
    }
    printf("\n");
    int min = delMin(heap,&n);
    printf("the heap after removing the minimum is\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",heap[i]);
    }
    printf("\n");
    return 0;
}