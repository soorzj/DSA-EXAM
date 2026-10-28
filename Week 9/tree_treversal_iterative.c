/***************************************************************
 * Program to implement binary tree in C using struct         *
 * and perform iterative traversals (without recursion)        *
 * Author: SOORAJ                                              *
 * Date: 10-8-26                                               *
 * Version: 3                                                  *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;
int nodeCount = 1;

// function prototypes
struct node *createChild(int parentValue, char *side);
void Inorder(int n);        // function to display inorder traversal iteratively
void Preorder(int n);       // function to display preorder traversal iteratively
void Postorder(int n);      // function to display postorder traversal iteratively

int main() {
    root = (struct node*)malloc(sizeof(struct node));
    printf("Enter root node value: ");
    scanf("%d", &root->data);
    root->left = createChild(root->data, "left");
    root->right = createChild(root->data, "right");

    printf("\nInorder Traversal:\n");
    Inorder(nodeCount);
    printf("\nPreorder Traversal:\n");
    Preorder(nodeCount);
    printf("\nPostorder Traversal:\n");
    Postorder(nodeCount);
    return 0;
}

struct node *createChild(int parentValue, char *side) {
    int exists;
    printf("Does the %s child of %d exist? (1/0): ", side, parentValue);
    scanf("%d", &exists);
    if (exists == 0)
        return NULL;

    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    printf("Enter %s child of %d: ", side, parentValue);
    scanf("%d", &newNode->data);
    nodeCount++;
    newNode->left = createChild(newNode->data, "left");
    newNode->right = createChild(newNode->data, "right");
    return newNode;
}

void Inorder(int n) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    struct node **stack = (struct node**)malloc(n * sizeof(struct node*));
    int top = -1;
    struct node *current = root;
    
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current; 
            current = current->left;
        }
        current = stack[top--];
        printf("%d\t", current->data);
        current = current->right;
    }
    free(stack);
    printf("\n");
}

void Preorder(int n) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    struct node **stack = (struct node**)malloc(n * sizeof(struct node*));
    int top = -1;
    stack[++top] = root;
    
    while (top != -1) {
        struct node *current = stack[top--];
        printf("%d\t", current->data);
        if (current->right)
            stack[++top] = current->right;
        if (current->left) 
            stack[++top] = current->left;
    }
    free(stack);
    printf("\n");
}

void Postorder(int n) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    struct node **stack1 = (struct node**)malloc(n * sizeof(struct node*));
    struct node **stack2 = (struct node**)malloc(n * sizeof(struct node*));
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    while (top1 != -1) {
        struct node *current = stack1[top1--];
        stack2[++top2] = current;
        if (current->left) 
            stack1[++top1] = current->left;
        if (current->right) 
            stack1[++top1] = current->right;
}

    while (top2 != -1) 
        printf("%d\t", stack2[top2--]->data);
    free(stack1);
    free(stack2);
    printf("\n");
}

