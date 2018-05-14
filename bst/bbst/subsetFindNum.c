#include<stdio.h>
#include<stdlib.h>
#include"findNum.c"

int subsetfindNum(struct Node* root, int l,int u,int r)
{
    return findNum(root, r + findRank(root,u) - 1);
}

// int main()
// {
//     int n;
//     printf("enter no of elements\n");
//     scanf("%d",&n);
//     printf("enter array\n");
//     struct Node* root = (struct Node*)malloc(sizeof(struct Node));
//     root = 0;
//     for(int i=0;i<n;i++)
//     {
//         int num;
//         scanf("%d",&num);
//         root = insert(root, num);
//     }
//     inorder(root);
//     printf("enter lwr and upr bounds\n");
//     int l,u;
//     scanf("%d %d",&l,&u);
//     printf("enter rank of number between %d and %d\n",l,u);
//     int r;
//     scanf("%d",&r);
//     printf("the number whose rank is %d in subset between %d and %d = %d\n",r,l,u,subsetfindNum(root,l,u,r));
//     return 0;
// }