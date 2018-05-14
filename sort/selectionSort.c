#include<stdio.h>
#include<stdlib.h>

int selectionSort(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        int min = arr[i];
        int pos = i,j;
        for(j=i+1;j<n;j++)
        {
            if(arr[j]<min)
            {
                min = arr[j];
                pos = j;
            }
        }
        if(pos != i)
        {
            int temp = arr[i];
            arr[i] = arr[pos];
            arr[pos] = temp;
        }
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
    selectionSort(arr,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}