#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int printarr(int arr[],int n)
{
    for(int i=0;i<n;i++) printf("%d ",arr[i]);
    printf("\n");
    return 0;
}

int reverse1(int arr[],int n)
{
    for(int i=0;i<n/2;i++)
    {
        int temp = arr[i];
        arr[i] =arr[n-i-1];
        arr[n-i-1] = temp;
    }
    return 0;
}

int reverse2(char arr[],int n)
{
    for(int i=0;i<n/2;i++)
    {
        char temp = arr[i];
        arr[i] =arr[n-i-1];
        arr[n-i-1] = temp;
    }
    return 0;
}

int push1(int arr[],int n,int *top)
{
    arr[++(*top)] = n;
    return 0;
}

int pop1(int arr[],int *top)
{
    int num = arr[(*top)];
    (*top)--;
    return num;
}

int push2(char arr[],char c,int *top)
{
    arr[++(*top)] = c;
    return 0;
}

char pop2(char arr[],int *top)
{
    char c = arr[(*top)--];
    return c;
}

int evaluate(char expression[])
{
    int top1=-1,top2=-1;
    int operand[50];
    char operator[50];
    int result = 0;
    int i=0;
    while(i<strlen(expression))
    {
        printf("i=%d\n",i);
        printf("expression=%c\n",expression[i]);
        printf("%d\n",atoi(&expression[i]));
        if(expression[i] != ' ')
        {
            if(atoi(&expression[i]) || expression[i]=='0')
            {
                push1(operand,atoi(&expression[i]),&top1);
                printf("operand pushed=%d\n",operand[top1]);
            }
            else
            {
                if(expression[i]=='(')
                {
                    char bracket[50];
                    int top = -1;
                    while(expression[++i]!=')')
                    {
                        push2(bracket,expression[i],&top);
                    }
                    push2(bracket,')',&top);
                    i++;
                    printf("bracket = %s\n",bracket);
                    push1(operand,evaluate(bracket),&top1);
                    printf("bracket pushed =%d\n",operand[top1]);
                }
                if(expression[i]=='*')
                {
                    i += 2;
                    int num1=pop1(operand,&top1);
                    int num2;
                    printf("number popped=%d\n",num1);
                    if(expression[i]=='(')
                    {
                        char bracket[50];
                        int top = -1;
                        while(expression[++i]!=')')
                        {
                            push2(bracket,expression[i],&top);
                        }
                        push2(bracket,')',&top);
                        i++;
                        printf("bracket = %s\n",bracket);
                        num2 = evaluate(bracket);
                        printf("bracket evaluated to %d\n",num2);
                    }
                    else{
                        num2 =atoi(&expression[i]);
                        i ++;
                    }
                    printf("next number=%d\n",num2);
                    push1(operand,num1*num2,&top1);
                    printf("number pushed=%d\n",operand[top1]);
                }
                else if(expression[i]=='/')
                {
                    i += 2;
                    int num1=pop1(operand,&top1);
                    int num2;
                    printf("number popped=%d\n",num1);
                    if(expression[i]=='(')
                    {
                        char bracket[50];
                        int top = -1;
                        while(expression[++i]!=')')
                        {
                            push2(bracket,expression[i],&top);
                        }
                        push2(bracket,')',&top);
                        i++;
                        printf("bracket = %s\n",bracket); 
                        num2 = evaluate(bracket);
                        printf("bracket evaluated to %d\n",num2);
                    }
                    else{
                        num2 =atoi(&expression[i]);
                        i++;
                    }
                    printf("next number=%d\n",num2);
                    push1(operand,num1/num2,&top1);
                    printf("number pushed=%d\n",operand[top1]); 
                }
                else if(expression[i]=='+' || expression[i]=='-')
                {
                    push2(operator,expression[i],&top2);
                    printf("operator pushed=%c\n",operator[top2]);
                }
            }
        }
        i++;
    }
    printf("result=%d\n",operand[top1]);
    printf("array b4 reverse\n");
    printarr(operand,top1+1);
    reverse2(operator,top2+1);
    reverse1(operand,top1+1);
    printf("array after reverse\n");
    printarr(operand,top1+1);
    while(top2!=-1)
    {
        char function = pop2(operator,&top2);
        int num1 = pop1(operand,&top1);
        int num2 = pop1(operand,&top1);
        printf("num1=%d num2=%d\n",num1,num2);
        if(function=='+')
        {
            push1(operand,num1+num2,&top1);
            printf("after adding...%d\n",operand[top1]);
        }
        else{
            push1(operand,num1-num2,&top1);           
        }
    }
    return pop1(operand,&top1); 
}

int main()
{
    char expression[10];
    scanf("%[^\n]s",expression);
    printf("%d\n",evaluate(expression));
    return 0;
}