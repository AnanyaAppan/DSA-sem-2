#include<stdio.h>
#include<stdlib.h>

int printArray(int arr[], int i,int j)
{
    for(int k=i;k<=j;k++) printf("%d ",arr[k]);
    printf("\n");
    return 0;
}

int swap(int arr[],int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int pivot(int arr[],int i,int j)
{
    int num = rand();
    return arr[(num%(j-i+1))+i];
}

int partition(int p,int arr[],int i,int j)
{
    int left = i;
    int right = j;
    while(left<=right)
    {
        while(left<=right && arr[left]<=p) left++;
        while(left<=right && arr[right]>p) right--;
        if(left<right)
        {
            swap(arr,left,right);
            left++;
            right--;
        }
    }
    if(left==j) return j;
    return right;
}

int quickSort(int arr[],int i,int j)
{
    //printf("i = %d j = %d\n",i,j);
    if(i==j)
    {
        return 0;
    }
    if(j-i==1)
    {
        //printf("yo!\n");
        if(arr[i]>arr[j])
        {
            swap(arr,i,j);
        }
        return 0;   
    }
    if(i<j)
    {
        int p = pivot(arr,i,j);
        //printf("the pivot element is %d\n",p);
        int k = partition(p,arr,i,j);
        printf("the partition is at %d\n",k);
        printf("the array after the first partition is \n");
        printArray(arr,i,j);
        quickSort(arr,i,k);
        quickSort(arr,k+1,j);
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
    printf("array before sorting\n");
    printArray(arr,0,n-1);
    quickSort(arr,0,n-1);
    printf("array after sorting\n");
    printArray(arr,0,n-1);
    return 0;
}
