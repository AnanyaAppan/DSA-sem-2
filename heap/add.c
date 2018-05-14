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

int add(int heap[], int* n, int num)
{
    heap[(*n)++] = num;
    bottomUpHeapify(*n-1,heap);
    return 0;
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
        int num;
        scanf("%d",&num);
        add(heap,&n, num);
        printf("enter 1 to add, 0 to exit\n");
        scanf("%d",&ans);
    }
    printf("the heap in level order is\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",heap[i]);
    }
    printf("\n");
    return 0;
}