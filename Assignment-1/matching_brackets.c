/******************************************************************************
 * Program to check matching brackets in an expression using	*
 * a stack implemented with an array	*
 * Author: SOORAJ	*
 * Date: 1-10-26	*
 * Version: 1	*
 ******************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// function prototypes
void push(char ch);                    // pushes a bracket onto the stack
char pop(void);                        // removes and returns the top bracket
int isEmpty(void);                     // returns 1 if the stack is empty
int isFull(void);                      // returns 1 if the stack is full
int isOpening(char ch);                // returns 1 for ( { [
int isClosing(char ch);                // returns 1 for ) } ]
int isMatching(char open, char close); // checks if two brackets form a pair
int checkBrackets(char expr[]);        // returns 1 if the expression is balanced

int main()
{
    int choice = -1;
    char expr[MAX];
    while (choice != 2)
    {
        printf("Menu for Bracket Matching\n");
        printf("1.Check an expression\n2.Exit\n");
        printf("Enter Your choice:\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter The expression:\n");
            scanf(" %99[^\n]", expr);
            if (checkBrackets(expr))
                printf("Brackets are balanced\n");
            else
                printf("Brackets are not balanced\n");
            break;
        case 2:
            printf("Exiting Program\n");
            break;
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}

void push(char ch)
{
    top++;
    stack[top] = ch;
}

char pop(void)
{
    char ch = stack[top];
    top--;
    return ch;
}

int isEmpty(void)
{
    return top == -1;
}

int isFull(void)
{
    return top == MAX - 1;
}

int isOpening(char ch)
{
    return ch == '(' || ch == '{' || ch == '[';
}

int isClosing(char ch)
{
    return ch == ')' || ch == '}' || ch == ']';
}

int isMatching(char open, char close)
{
    if (open == '(' && close == ')')
        return 1;
    if (open == '{' && close == '}')
        return 1;
    if (open == '[' && close == ']')
        return 1;
    return 0;
}

int checkBrackets(char expr[])
{
    top = -1;
    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (isOpening(expr[i]))
        {
            if (isFull())
            {
                printf("Stack overflow, expression too long\n");
                return 0;
            }
            push(expr[i]);
        }
        else if (isClosing(expr[i]))
        {
            if (isEmpty())
            {
                printf("Extra '%c' found at position %d\n", expr[i], i + 1);
                return 0;
            }
            char open = pop();
            if (!isMatching(open, expr[i]))
            {
                printf("Mismatch '%c' and '%c' at position %d\n", open, expr[i], i + 1);
                return 0;
            }
        }
    }
    if (!isEmpty())
    {
        printf("Opening '%c' was never closed\n", stack[top]);
        return 0;
    }
    return 1;
}
