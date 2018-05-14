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
    //printf("array\n");
    //printArray(arr,i,j);
    int count=0;
    int left = i, right = k+1;
    int B[100];
    int p=i;
    while(left<k+1 && right<j+1)
    {
        if(arr[left]<arr[right] && left<=k)
        {
            B[p++] = arr[left++];
        }
        else if(right>=k+1)
        {
        //    printf("right = %d k = %d\n",right,k);
            count += k-left+1;
            B[p++] = arr[right++];  
        }
        //printf("count = %d\n",count);
    }
    //if(right==j+1) count += (k-left)*(j-k);
    //printf("count = %d\n",count);
    while(left<=k)
    {
        B[p++] = arr[left++];
    } 
    while(right<=j)
    {
        B[p++] = arr[right++];
    }
    for(int n=i;n<=j;n++) arr[n] = B[n];
    return count;
}

int inversions(int arr[],int i,int j)
{
    int count = 0;
    if(i==j) return 0;
    int k = (i+j)/2;
    int count1 = inversions(arr,i,k);
    //printf("inversions on left = %d\n",count1);
    int count2 = inversions(arr,k+1,j);
    //printf("inversions on left = %d\n",count1);
    count += merge(arr,i,k,j);
    count += count1 + count2;
    //printf("total = %d\n",count);
    return count;
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
    int count = inversions(arr,0,n-1);
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    printf("the number of inversions = %d\n",count);
    return 0;
}