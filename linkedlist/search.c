#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

int insertBeg(struct node **head, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->next = (*head);
    *head = temp;
    temp->data = data;
    return 0;
}

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

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head = NULL;
    insertBeg(&head,3);
    insertBeg(&head,4);
    insertBeg(&head,5);
    insertBeg(&head,6);    
    printList(head);
    printf("\n");
    printf("enter a number to search for\n");
    int num;
    scanf("%d",&num);
    int pos = search(head,num);
    if(pos!=-1)
    {
        printf("number found at %d!\n",pos);
    }
    else
    {
        printf("Oops! Couldn't find the number\n");
    }
    return 0;
}