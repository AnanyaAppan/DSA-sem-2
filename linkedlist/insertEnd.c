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

int insertEnd(struct node **head, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if(*head == NULL){
        insertBeg(head,data);
        return 0;
    }
    struct node *temp2 = (struct node *)malloc(sizeof(struct node));
    temp2 = *head;
    while(temp2->next != NULL)
    {
        temp2 = temp2->next;
    }
    temp->next = NULL;
    temp2->next = temp;
    temp->data = data;
    return 0;
}

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head = NULL;
    insertEnd(&head,3);
    insertEnd(&head,4);
    insertEnd(&head,5);
    insertEnd(&head,6);    
    printList(head);
    return 0;
}