#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a[100][100], c[100][100];
    int n;
    printf("enter the size of the matrix\n");
    scanf("%d",&n);
    printf("enter array elements\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            c[i][j] = a[i][j];
        }
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
            if(c[i][j]>c[i][k]+c[k][j]) 
                c[i][j]=c[i][k]+c[k][j];
    printf("the elements of duplicate matrix are\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }   
    return 0;
}
