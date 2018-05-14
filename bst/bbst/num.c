#include<stdio.h>
#include<stdlib.h>
#include"FindRank.c"

int num(struct Node* root ,int x, int y)
{
    int num1, num2;
    num1 = x>y?  x:y;
    num2 = x+y-num1;
    return findRank(root, num2) - findRank(root, num1) + 1;
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
//     printf("enter two numbers in the array\n");
//     int x,y;
//     scanf("%d %d",&x,&y);
//     printf("the no of nos between them = %d\n",num(root,x,y));
//     return 0;
// }