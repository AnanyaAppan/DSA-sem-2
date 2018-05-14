#include<stdio.h>
#include<stdlib.h>


int push(int arr[],int n,int *top)
{
    if(*top == n)
    {
        printf("stack full\n");
        return 0;
    }
    arr[++(*top)] = n;
    return 0;
}

int pop(int arr[],int *top)
{
    if(*top == -1)
    {
        printf("stack empty\n");
        return 0;
    }
    int num = arr[(*top)--];
    return num;
}

int main()
{
    int arr[3] = {},top=-1;
    push(arr,1,&top);
    push(arr,2,&top);
    push(arr,3,&top);
    printf("%d\n",pop(arr,&top));
    push(arr,4,&top);
    for(int i=0;i<3;i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}