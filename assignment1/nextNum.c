#include<stdio.h>
#include<stdlib.h>


int push(int arr[],int n,int *top)
{
    arr[++(*top)] = n;
    return 0;
}

int pop(int arr[],int *top)
{
    int num = arr[(*top)--];
    return num;
}

int* nextNum(int arr[], int n)
{
    int stack[100],top = -1;
    int* res;
    res = (int *) malloc(n*sizeof(int));
    res[n-1] = -1;
    push(stack,n-1,&top);
    for(int i = n-2;i>=0;i--)
    {
        if(arr[i]<arr[i+1])
        {
            res[i] = i+1;
            push(stack,i,&top);
        }
        else
        {
            while(top!=-1)
            {
                if(arr[stack[top]]<arr[i])
                {
                    pop(stack,&top);
                }
                else
                    break;
            }
            push(stack,i,&top);
            if(top==0) res[i] = -1;
            else res[i] = stack[top-1];
        }
    }
    return res;
}

int main()
{
    int n;
    scanf("%d",&n);
    int arr[100];
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    int * res = (int *)malloc(n*sizeof(int));
    res = nextNum(arr,n);
    for(int i=0;i<n;i++) printf("%d ",res[i]);
    printf("\n");
    free(res);
    return 0;
}