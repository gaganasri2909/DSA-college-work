#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define max 15
int stack[max];
int top=-1;
void push(int item)
{
    if(top>max-1)
    {
        printf("stack overflow\n");
    }
    else{
        stack[++top]=item;
    }
}
int pop()
{
    if(top<0)
    {
        printf("stack underflow\n");
    }
    else{
        return stack[top--];
    }
}
int evaluatepostfix(char* postfix)
{
    int i,op1,op2;
    int res;
    char ch;
    for(i=0;postfix[i]!='\0';i++)
    {
        ch=postfix[i];
        if(isdigit(ch))
        {
            push(ch-'0');
        }
        else
        {
            op2=pop();
            op1=pop();
            switch(ch)
            {
                case'+':res=op1+op2;
                break;
                case'-':res=op1-op2;
                break;
                case'*':res=op1*op2;
                break;
                case'/':res=op1/op2;
                break;
                default:
                printf("invalid choice encountered");
            }
            push(res);
        }
    }
    return pop();
}
int main()
{
    char postfix[max];
}