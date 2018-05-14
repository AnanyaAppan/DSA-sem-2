#include<stdio.h>
#include<stdlib.h>
#include"subsetFindNum.c"

int num(struct Node* root ,int x, int y)
{
    int num1, num2;
    num1 = x>y?  x:y;
    num2 = x+y-num1;
    return findRank(root, num2) - findRank(root, num1) + 1;
}

int subsetMedian(struct Node* root, int l,int u)
{
    return subsetfindNum(root,l,u,(num(root,l,u)+1)/2);
}

int main()
{
    int n;
    printf("enter no of elements\n");
    scanf("%d",&n);
    printf("enter array\n");
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root = 0;
    for(int i=0;i<n;i++)
    {
        int num;
        scanf("%d",&num);
        root = insert(root, num);
    }
    inorder(root);
    printf("enter lwr and upr bounds\n");
    int l,u;
    scanf("%d %d",&l,&u);
    printf("the median in subset between %d and %d = %d\n",l,u,subsetMedian(root,l,u));
    return 0;
}