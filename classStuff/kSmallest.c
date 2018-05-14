#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

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
        //printf("left = %d right = %d\n",left,right);
        if(left<right)
        {
            swap(arr,left,right);
            left++;
            right--;
        }
        //printf("array after swap\n");
        //printArray(arr,i,j);
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
    if(i<j)
    {
        int p = pivot(arr,i,j);
        //printf("pivot = %d\n",p);
        int k = partition(p,arr,i,j);
        //printf("array after partition is\n");
        //printArray(arr,i,j);
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

int kSmallestNumbers(int k)
{
    int arr[1000000];
    int n;
    scanf("%d",&n);
    int i=0;
    int num;
    if(n<2*k) num = n;
    else num = 2*k; 
    while(i<num)
    {
        scanf("%d",&arr[i]);
        i++;
        n--;
    }  
    //printf("array scanned = \n");
    //printArray(arr,0,num-1);
    int p = findRank(arr,(num+1)/2+1,0,num-1);
    //printf("median = %d\n",p);
    int mid = partition(p,arr,0,num-1);
    //printf("median found at %d\n",mid);
    while(n>0)
    {
        int i=mid+1;
        while(i<num && n>0)
        {
            scanf("%d",&arr[i]);
            i++;
            n--;
        }
        p = findRank(arr,(num+1)/2+1,0,num-1);
        mid = partition(p,arr,0,num-1);
    }
    for(int i=0;i<k;i++) printf("%d ",arr[i]);
    printf("\n");
    return 0;
}

int main()
{
    int k;
    scanf("%d",&k);
    kSmallestNumbers(k);
    return 0;
}