/***************************************************************
 * Program to implement priority queue as a linked list        *
 * Version: 1                                                  *
 * Date: 10-8-26                                               *
 * Author: Sooraj                                              *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    int priority;
    struct node *next;
};

struct node *head = NULL;

/* function prototypes */
void enqueue(int value, int priority); //fucntion that inserts the element with its priority at the back
int dequeueHighest(void);              //fucntion that checks for queue empty and dequeues the element with highest priority
int dequeueLowest(void);               //fucntion that checks for queue empty and dequeues the element with lowest priority
int seeHighest(void);                  //fucntion that checks for queue empty and just prints the element with highest priority 
int seeLowest(void);                   //fucntion that checks for queue empty and just prints the element with lowest priority
void print_queue(void);                //fucntion that checks for queue empty and prints the elements in order
int isEmpty(void);                     //fucntion that checks if the linked list is empty

int main() {
    int choice = -1;
    printf("Menu for Linked List Priority Queue\n");
    printf("1.Enqueue\n2.Dequeue Highest Priority\n3.Dequeue Lowest Priority\n4.See Highest Member\n5.See Lowest Member\n6.See the queue in order\n7.Exit\n");
    
    while (choice != 7) {
        int dequeued;
        printf("Enter Your choice:\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            {
                int val, priority;
                printf("Enter element to be queued:\n");
                scanf("%d", &val);
                printf("Enter its priority:\n");
                scanf("%d", &priority);
                enqueue(val, priority);
                break;
            }
            case 2:
            {
                dequeued = dequeueHighest();
                if (dequeued != -1)
                    printf("Highest Priority Element dequeued: %d\n", dequeued);
                break;
            }
            case 3:
            {
                dequeued = dequeueLowest();
                if (dequeued != -1)
                    printf("Lowest Priority Element dequeued: %d\n", dequeued);
                break;
            }
            case 4:
            {
                int highest = seeHighest();
                if (highest != -1)
                    printf("Topmost priority Element of queue: %d\n", highest);
                break;
            }
            case 5:
            {
                int least = seeLowest();
                if (least != -1)
                    printf("Least Priority Element of queue: %d\n", least);
                break;
            }
            case 6:
                print_queue();
                break;
            case 7:
                printf("Exiting the Program\n");
                break;
            default:
                printf("Wrong Choice\n");
                break;
        }
    }
    return 0;
}

void enqueue(int value, int priority) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->priority = priority;
    newNode->next = NULL;
    
    if (head == NULL) {
        head = newNode;
        printf("Queued\n");
        return;
    }
    
    struct node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    printf("Queued\n");
}

int dequeueHighest() {
    if (isEmpty() == 1) {
        printf("Queue is Empty\n");
        return -1;
    }
    
    struct node *current = head;
    struct node *highestNode = head;
    struct node *highestPrev = NULL;
    struct node *prev = NULL;

    while (current != NULL) {
        if (current->priority > highestNode->priority) {
            highestNode = current;
            highestPrev = prev;
        }
        prev = current;
        current = current->next;
    }

    int val = highestNode->data;
    
    if (highestPrev == NULL) { 
        head = head->next;
    } else {
        highestPrev->next = highestNode->next;
    }
    
    free(highestNode);
    return val;
}
    
int dequeueLowest() {
    if (isEmpty() == 1) {
        printf("Queue is Empty\n");
        return -1;
    }
    
    struct node *current = head;
    struct node *lowestNode = head;
    struct node *lowestPrev = NULL;
    struct node *prev = NULL;

    while (current != NULL) {
        if (current->priority < lowestNode->priority) {
            lowestNode = current;
            lowestPrev = prev;
        }
        prev = current;
        current = current->next;
    }

    int val = lowestNode->data;
    
    if (lowestPrev == NULL) { 
        head = head->next;
    } else {
        lowestPrev->next = lowestNode->next;
    }
    
    free(lowestNode);
    return val;
}
    
int seeHighest() {
    if (isEmpty() == 1) {
        printf("Queue is Empty\n");
        return -1;
    }
    
    struct node *current = head;
    struct node *highestNode = head;

    while (current != NULL) {
        if (current->priority > highestNode->priority) {
            highestNode = current;
        }
        current = current->next;
    }
    return highestNode->data;
}

int seeLowest() {
    if (isEmpty() == 1) {
        printf("Queue is Empty\n");
        return -1;
    }
    
    struct node *current = head;
    struct node *lowestNode = head;

    while (current != NULL) {
        if (current->priority < lowestNode->priority) {
            lowestNode = current;
        }
        current = current->next;
    }
    return lowestNode->data;
}
    
void print_queue() {
    if (isEmpty() == 1) {
        printf("Queue is Empty\n");
        return;
    }

    printf("Displaying the queue:\nElement\tPriority\n");
    struct node *current = head;
    while (current != NULL) {
        printf("%d\t%d\n", current->data, current->priority);
        current = current->next;
    }
}
    
int isEmpty() {
    if (head == NULL)
        return 1;
    else
        return 0;
}
