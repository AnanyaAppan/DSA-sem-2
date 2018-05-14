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

int insertPos(struct node **head,int data, int pos )
{
    int cur = 1;
    if(pos==1)
    {
        insertBeg(head,data);
        return 0;
    }
    else
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        struct node *temp2 = (struct node *)malloc(sizeof(struct node));
        temp2 = *head;
        while(cur != pos-1)
        {
            temp2 = temp2->next;
            cur ++;
        }
        temp->next = temp2->next;
        temp2->next = temp;
        temp->data = data;
        return 0;
    }
}

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head = NULL;
    insertBeg(&head,3);
    insertBeg(&head,4);
    insertBeg(&head,5);    
    printList(head);
    printf("\n");
    insertPos(&head,6,4);
    printList(head);
    return 0;
}