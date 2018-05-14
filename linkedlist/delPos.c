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

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head = NULL;
    insertBeg(&head,3);
    insertBeg(&head,4);
    insertBeg(&head,5);    
    printList(head);
    printf("\n");
    delPos(&head,3);
    printList(head);
    return 0;
}