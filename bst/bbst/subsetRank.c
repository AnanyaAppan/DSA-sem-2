#include<stdio.h>
#include<stdlib.h>
#include"FindRank.c"

int subsetRank(struct Node* root, int l,int u,int x)
{
    return findRank(root,x) - findRank(root, u) + 1;
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
    printf("enter number between %d and %d\n",l,u);
    int x;
    scanf("%d",&x);
    printf("the rank of %d in subset between %d and %d = %d\n",x,l,u,subsetRank(root,l,u,x));
    return 0;
}