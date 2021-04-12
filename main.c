#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    char data;
    struct stack* next;
}stack;

void push(int a, stack* S)

{
    stack* p;
    p = (stack*)malloc(sizeof(stack));
    p->data = a;
    p->next = S->next;
    S->next = p;
}

int pop(stack* S)
{
    char a;
    stack* p = S->next;
    a = p->data;
    S->next = p->next;
    free(p);
    return (a);
}

int priority(char x)
{

    if (x == '(') {

        return 1;
    }

    else if (x == ')') {

        return 2;
    }

    else if (x == '=') {

        return 3;
    }

    else if (x == '+' || x == '-') {

        return 4;
    }

    else if (x == '*' || x == '/') {

        return 5;
    }

    return 6;

}

void infix_to_postfix(char* infix, char* postfix, stack* S)
{
    int i = 0, j = 0;
    while (infix[i] != '\0')
    {
        if (infix[i] >= '0' && infix[i] <= '9')
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            push(infix[i], S);
        }
        else if (infix[i] == ')')
        {
            while (S->next->data != '(') {
                postfix[j++] = pop(S);
            }
            pop(S);
        }
        else
        {
            while (S->next != NULL && priority(infix[i]) <= priority(S->next->data))
            {
                postfix[j++] = pop(S);
            }
            push(infix[i], S);
        }
        i++;
    }

    while (S->next != NULL)
    {
        postfix[j++] = pop(S);
    }

    puts(postfix);
}

int main(void)
{
    stack* S = (stack*)malloc(sizeof(stack));
    S->next = NULL;
    char infix[20];
    char postfix[20];
    scanf("%s", infix);
    infix_to_postfix(infix, postfix, S);

    return 0;
}