#include<stdio.h>
#include<stdlib.h>

int printArray(int arr[], int i,int j)
{
    for(int k=i;k<=j;k++) printf("%d ",arr[k]);
    printf("\n");
    return 0;
}

int countSort(int arr[],int n,int exp)
{
    int c[10],b[1000];
    for(int i=0;i<10;i++) c[i] = 0;
    for(int i=0;i<n;i++) c[((arr[i])/exp)%10]++;
    for(int i=1;i<10;i++) c[i] += c[i-1];
    printf("c\n");
    printArray(c,0,9);
    for(int i=n-1;i>=0;i--)
    {
        b[c[((arr[i])/exp)%10]-1] = arr[i];
        c[((arr[i])/exp)%10] --;
    }
    printf("b\n");
    printArray(b,0,n-1);
    for(int i=0;i<n;i++) arr[i] = b[i];
    return 0;
}

int findDigits(int n)
{
    int count = 0;
    while(n!=0)
    {
        n/=10;
        count++;
    }
    return count;
}

int radixSort(int arr[],int n)
{
    int flag = 1;
    int maxDigit = 0;
    for(int i=0;i<n;i++)
    {
        int digit = findDigits(arr[i]);
        if(digit>maxDigit) maxDigit = digit;
    }
    int y=1,count = 0;
    while(count<maxDigit)
    {
        countSort(arr,n,y);
        y*=10;
        count++;
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
    radixSort(arr,n);
    printf("array after sorting\n");
    printArray(arr,0,n-1);
    return 0;
}