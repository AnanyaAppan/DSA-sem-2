#include<stdio.h>
#include<stdlib.h>

int printArray(int arr[], int i,int j)
{
    for(int k=i;k<=j;k++) printf("%d ",arr[k]);
    printf("\n");
    return 0;
}

int countSort(int arr[],int n)
{
    int c[1000],b[1000];
    for(int i=0;i<1000;i++) c[i] = 0;
    for(int i=0;i<n;i++) c[arr[i]-1]++;
    for(int i=1;i<1000;i++) c[i] += c[i-1];
    printArray(c,0,n-1);
    for(int i=n-1;i>=0;i--)
    {
        b[c[arr[i]-1]-1] = arr[i];
        c[arr[i]-1] --;
    }
    for(int i=0;i<n;i++) arr[i] = b[i];
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
    printf("array before sorting\n");
    printArray(arr,0,n-1);
    countSort(arr,n);
    printf("array after sorting\n");
    printArray(arr,0,n-1);
    return 0;
}