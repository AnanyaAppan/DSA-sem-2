#include<stdio.h>
#include<stdlib.h>

int search(int arr[],int n,int num)
{
    int pos = -1;
    int i = 0;
    for(i;i<n;i++)
    {
        if(arr[i]==num)
        {
            pos = i;
            break;
        }
    }
    return pos;
}

int main()
{
    int n;
    printf("enter size of stack\n");
    scanf("%d",&n);
    int stack[100];
    printf("enter stack\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&stack[i]);
    }
    int arr[100];
    printf("enter sequence after popping\n");
    for(int i=0;i<n;i++)
    {
        int num;
        scanf("%d",&num);
        int pos = search(stack,n,num);
        arr[i] = pos;
    }
    int lastPos = search(arr,n,n-1);
    int flag = 0;
    for(int i=0;i<lastPos;i++)
    { 
        if(arr[i+1]<arr[i])
        {
            flag = 1;
            break;
        }
    }
    if(flag)
    {
        printf("sequence impossible\n");
        return 0;
    }
    for(int i=lastPos;i<n-1;i++)
    { 
        if(arr[i+1]>arr[i])
        {
            flag = 1;
            break;
        }
    }
    if(flag)
    {
        printf("sequence impossible\n");
    }
    else
    {
        printf("correct sequence\n");
    }
    return 0;
}
    
