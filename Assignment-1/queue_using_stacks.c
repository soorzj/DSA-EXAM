/******************************************************************************
 * Program to implement a normal queue using two stacks	*
 * (stacks are implemented using linked list)	*
 * Author: SOORAJ	*
 * Date: 1-10-26	*
 * Version: 1	*
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *stack1 = NULL;
struct node *stack2 = NULL;

// function prototypes
void push(struct node **top, int val); // pushes a value onto the given stack
int pop(struct node **top);            // pops and returns the top value
int isEmpty(struct node *top);         // returns 1 if the given stack is empty
void transfer(void);                   // moves all elements from stack1 to stack2
void enqueue(int val);                 // adds an element at the rear of the queue
void dequeue(void);                    // removes the element at the front
void front(void);                      // shows the element at the front
void displayQueue(void);               // prints the queue from front to rear
void printReverse(struct node *top);   // prints a stack from bottom to top
void clearStack(struct node **top);    // frees every node of the given stack

int main(){
    int choice = -1, val;
    while (choice != 5){
        printf("Menu for Queue using Stacks\n");
        printf("1.Enqueue\n2.Dequeue\n3.Front Element\n");
        printf("4.Display Queue\n5.Exit\n");
        printf("Enter Your choice:\n");
        scanf("%d", &choice);
        switch (choice){
		    case 1:
		        printf("Enter The element:\n");
		        scanf("%d", &val);
		        enqueue(val);
		        break;
		    case 2:
		        dequeue();
		        break;
		    case 3:
		        front();
		        break;
		    case 4:
		        displayQueue();
		        break;
		    case 5:
		        clearStack(&stack1);
		        clearStack(&stack2);
		        printf("Exiting Program\n");
		        break;
		    default:
		        printf("Wrong choice\n");
        }
    }
    return 0;
}

void push(struct node **top, int val){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = val;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct node **top){
    struct node *temp = *top;
    int val = temp->data;
    *top = temp->next;
    free(temp);
    return val;
}

int isEmpty(struct node *top){
    return top == NULL;
}

void transfer(void){
    while (!isEmpty(stack1))
    	push(&stack2, pop(&stack1));
}

void enqueue(int val){
    push(&stack1, val);
    printf("Element %d enqueued\n", val);
}

void dequeue(void){
    if (isEmpty(stack2))
        transfer();
    if (isEmpty(stack2)){
        printf("Queue is empty\n");
        return;
    }
    printf("Element %d dequeued\n", pop(&stack2));
}

void front(void){
    if (isEmpty(stack2))
        transfer();
    if (isEmpty(stack2)){
        printf("Queue is empty\n");
        return;
    }
    printf("Front element: %d\n", stack2->data);
}

void displayQueue(void){
    if (isEmpty(stack1) && isEmpty(stack2)){
        printf("Queue is empty\n");
        return;
    }
    struct node *current = stack2;
    printf("Queue (front to rear):\n");
    while (current != NULL){
        printf("%d\t", current->data);
        current = current->next;
    }
    printReverse(stack1);
    printf("\n");
}

void printReverse(struct node *top){
    if (top == NULL)
        return;
    printReverse(top->next);
    printf("%d\t", top->data);
}

void clearStack(struct node **top){
    while (!isEmpty(*top))
        pop(top);
}
