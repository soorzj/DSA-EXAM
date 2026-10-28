/******************************************************************************
 * Program to implement two stacks using a single array	*
 * Author: SOORAJ	*
 * Date: 1-10-26	*
 * Version: 1	*
 ******************************************************************************/

#include <stdio.h>

#define MAX 6

int arr[MAX];
int top1 = -1;
int top2 = MAX;

// function prototypes
void push1(int val); // pushes a value onto stack 1 (grows from left)
void push2(int val); // pushes a value onto stack 2 (grows from right)
void pop1(void);     // pops the top value of stack 1
void pop2(void);     // pops the top value of stack 2
void display1(void); // prints stack 1 from top to bottom
void display2(void); // prints stack 2 from top to bottom

int main()
{
    int choice = -1, val;
    while (choice != 7)
    {
        printf("Menu for Two Stacks in One Array\n");
        printf("1.Push to Stack 1\n2.Push to Stack 2\n");
        printf("3.Pop from Stack 1\n4.Pop from Stack 2\n");
        printf("5.Display Stack 1\n6.Display Stack 2\n7.Exit\n");
        printf("Enter Your choice:\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter The element:\n");
            scanf("%d", &val);
            push1(val);
            break;
        case 2:
            printf("Enter The element:\n");
            scanf("%d", &val);
            push2(val);
            break;
        case 3:
            pop1();
            break;
        case 4:
            pop2();
            break;
        case 5:
            display1();
            break;
        case 6:
            display2();
            break;
        case 7:
            printf("Exiting Program\n");
            break;
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}

void push1(int val)
{
    if (top1 + 1 == top2)
    {
        printf("Stack overflow, array is full\n");
        return;
    }
    top1++;
    arr[top1] = val;
    printf("%d pushed to Stack 1\n", val);
}

void push2(int val)
{
    if (top1 + 1 == top2)
    {
        printf("Stack overflow, array is full\n");
        return;
    }
    top2--;
    arr[top2] = val;
    printf("%d pushed to Stack 2\n", val);
}

void pop1(void)
{
    if (top1 == -1)
    {
        printf("Stack 1 is empty\n");
        return;
    }
    printf("%d popped from Stack 1\n", arr[top1]);
    top1--;
}

void pop2(void)
{
    if (top2 == MAX)
    {
        printf("Stack 2 is empty\n");
        return;
    }
    printf("%d popped from Stack 2\n", arr[top2]);
    top2++;
}

void display1(void)
{
    if (top1 == -1)
    {
        printf("Stack 1 is empty\n");
        return;
    }
    printf("Stack 1 (top to bottom):\n");
    for (int i = top1; i >= 0; i--)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void display2(void)
{
    if (top2 == MAX)
    {
        printf("Stack 2 is empty\n");
        return;
    }
    printf("Stack 2 (top to bottom):\n");
    for (int i = top2; i < MAX; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}
