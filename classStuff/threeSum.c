#include<stdio.h>
#include<stdlib.h>

int printArray(int arr[],int i,int j)
{
    for(int k=i;k<=j;k++) printf("%d ",arr[k]);
    printf("\n");
    return 0;
}

int findTriplet(int triplet[],int arr[],int n)
{
    //int triplet[3] = {-1,-1,-1};
    
    for(int i=0;i<n;i++)
    {
        int sum = arr[i];
        int left = 0;
        int right = n-1;
        printf("sum = %d\n",sum);
        while(left<=right && left!=n && right!=-1)
        {
            //printf("left = %d right = %d\n",left,right);
            int currsum = arr[left]+arr[right];
            //printf("current sum = %d\n",currsum);
            if(currsum==sum)
            {
                triplet[0] =  arr[left];
                triplet[1] = arr[right];
                triplet[2] = sum;
                left++;
                right--;
            }
            else if(currsum>sum)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }
    return 0;
}

int main()
{
    printf("enter size\n");
    int n;
    int arr[1000000];
    scanf("%d",&n);
    printf("enter array\n");
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    int triplet[3]={-1,-1,-1};
    findTriplet(triplet,arr,n);
    printArray(triplet,0,2);
    return 0;
}