#include<stdio.h>
#include<stdlib.h>

int printArray(int arr[], int n)
{
    for(int i=0;i<n;i++) printf("%d ",arr[i]);
    printf("\n");
    return 0;
}

int insertionSort(int arr[],int n)
{
    for(int i=1;i<n;i++)
    {
        int j = i-1;
        int num = arr[i];
        while(num<arr[j] && j>=0)
        {
            arr[j+1] = arr[j];
            j--;
            printArray(arr,n);
        }
        arr[j+1] = num;
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
    insertionSort(arr,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}