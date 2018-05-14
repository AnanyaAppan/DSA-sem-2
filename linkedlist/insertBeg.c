#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

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

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head = NULL;
    insertBeg(&head,3);
    insertBeg(&head,4);    
    printList(head);
    return 0;
}