#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;

int search(struct node *head,int num)
{
    int ans = 0;
    while(head != NULL)
    {
        if(head->data == num)
        {
            return ans;
        }
        head = head->next;
        ans++;
    }
    return -1;
}

int printList(struct node *head)
{
    while(head != NULL)
    {
        printf("%d\t",head->data);
        head = head->next;
    }
    return 0;
}

int insertBeg(struct node **head, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->next = (*head);
    *head = temp;
    temp->data = data;
    return 0;
}

int delBeg(struct node **head)
{
    if(*head != NULL)
    {   
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return 0;
    }
}

int delPos(struct node **head, int pos)
{
    if(head != NULL)
    {
        if(pos == 1)
        {
            delBeg(head);
            return 0;
        }
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        struct node *temp2 = (struct node *)malloc(sizeof(struct node));
        temp = *head;
        int cur = 1;
        while(cur != pos)
        {
            temp2 = temp;
            temp = temp->next;
            cur++;
        }
        temp2->next = temp->next;
        free(temp);
        return 0;
    }
    return 1;
}

int hash(int x)
{
    int p = 100003;
    return x%p;
}

int add(int x, node* arr[])
{
    int pos = hash(x);
    insertBeg(&arr[pos],x);
    return 0;
}

int del(int x, node* arr[])
{
    int pos1 = hash(x);
    int pos2 = search(arr[pos1],x);
    if(pos2==-1) printf("not found!!\n");
    else
        delPos(&arr[pos1],pos2+1);
    return 0; 
}

int HashTableSearch(int x,node* arr[])
{
    int pos = hash(x);
    if(search(arr[pos],x)!=-1) printf("element found!\n");
    else printf("not found\n");
    return 0;
}

int main()
{
    node* arr[100003];
    int loop = 1;
    while(loop)
    {
        int choice;
        printf("enter 1 to add, 2 to del and 3 to search: ");
        scanf("%d",&choice);
        int num;
        printf("enter number\n");
        scanf("%d",&num);
        if(choice==1)
        {
            add(num,arr);
        }
        else if(choice==2)
        {
            del(num,arr); 
        }
        else{
            HashTableSearch(num,arr);
        }
        printf("enter 0 to exit or 1 to continue: \n");
        scanf("%d",&loop);
    }
    return 0;
}

