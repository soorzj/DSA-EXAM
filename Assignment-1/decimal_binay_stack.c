/******************************************************************************
 * Program to convert a decimal number to binary using a stack	*
 * Author: SOORAJ	*
 * Date: 1-10-26	*
 * Version: 1	*
 ******************************************************************************/

#include <stdio.h>

#define MAX 32

int stack[MAX];
int top = -1;

// function prototypes
void push(int val);            // pushes a binary digit onto the stack
int pop(void);                 // removes and returns the top digit
int isEmpty(void);             // returns 1 if the stack is empty
int isFull(void);              // returns 1 if the stack is full
void decimalToBinary(int num); // converts num to binary and prints it

int main()
{
    int choice = -1, num;
    while (choice != 2)
    {
        printf("Menu for Decimal to Binary Conversion\n");
        printf("1.Convert a number\n2.Exit\n");
        printf("Enter Your choice:\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter The decimal number:\n");
            scanf("%d", &num);
            if (num < 0)
            {
                printf("Enter a non-negative number\n");
                break;
            }
            decimalToBinary(num);
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

void push(int val)
{
    top++;
    stack[top] = val;
}

int pop(void)
{
    int val = stack[top];
    top--;
    return val;
}

int isEmpty(void)
{
    return top == -1;
}

int isFull(void)
{
    return top == MAX - 1;
}

void decimalToBinary(int num)
{
    int original = num;
    top = -1;
    if (num == 0)
    {
        push(0);
    }
    while (num > 0)
    {
        if (isFull())
        {
            printf("Stack overflow\n");
            return;
        }
        push(num % 2);
        num = num / 2;
    }
    printf("Binary of %d is: ", original);
    while (!isEmpty())
    {
        printf("%d", pop());
    }
    printf("\n");
}
