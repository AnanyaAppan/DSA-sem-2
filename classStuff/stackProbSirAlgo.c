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

int main()
{
    int n,top=-1;
    printf("enter number\n");
    scanf("%d",&n);
    int arr[50]={0},input[50];
    printf("enter the input array\n");
    for(int i=0;i<n;i++) scanf("%d",&input[i]);
    int flag=1;
    int i=1;
    int j=0;
    while(i!=n+1)
    {
        printf("i=%d\n",i);
        printf("input=%d\n",input[j]);
        if(top==-1)
        {
            push(arr,i,&top);
            printf("pushing %d\n",i);
            i++;
        }
        if(arr[top]==input[j])
        {
            printf("popping %d\n",arr[top]);
            pop(arr,&top);
            j++;
        }
        else{
            push(arr,i,&top);
            printf("pushing %d\n",i);
            i++;
        }
    }
    for(int i=0;i<=top;i++) printf("%d ",arr[i]);
    printf("\n");
    //printf("%d\n",top);
    for(int i=0;i<=top;i++)
    {
        if(arr[i]!=input[j]) 
        {
            flag = 0;
            break;
        }
        j++;
    }
    if(flag) printf("yes!!\n");
    else printf("no :p\n");
    return 0;
}