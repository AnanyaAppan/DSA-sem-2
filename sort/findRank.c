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

int findRank(int arr[],int r,int i,int j)
{
    if(i==j)
    {
        if(r==1) return arr[i];
    }
    if(i<=j)
    {
        int p = pivot(arr,i,j);
        int k = partition(p,arr,i,j);
        printf("array after partition is\n");
        printArray(arr,i,j);
        if(arr[k]==p)
        {
            if(j-k+1==r) return p;
            else if(j-k+1>r) return findRank(arr,r,k+1,j);
            else return findRank(arr,r-(j-(k-1)),i,k-1);
        }
        else{
            findRank(arr,r,i,j);
        }
    }
}

int main()
{
    int n;
    printf("enter size of the array\n");
    scanf("%d",&n);
    printf("enter the array\n");
    int arr[100];
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    printf("enter rank(1<=rank<=n)\n");
    int r;
    scanf("%d",&r);
    int num = findRank(arr,r,0,n-1);
    printf("the number with rank %d is %d\n",r,num);
    return 0;
}