/***************************************************************
 * Program to implement Binary Tree in C using struct         *
 * and perform tree traversals using RECURSION                 *
 * Author: SOORAJ                                              *
 * Date: 10-8-26                                               *
 * Version: 5                                                  *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;

// Function Prototypes
struct node *createChild(int parentValue, char *side);
void Inorder(struct node *ptr);
void Preorder(struct node *ptr);
void Postorder(struct node *ptr);

int main() {
    root = (struct node*)malloc(sizeof(struct node));
    printf("Enter root node value: ");
    scanf("%d", &root->data);
    root->left = createChild(root->data, "left");
    root->right = createChild(root->data, "right");

    printf("\nInorder Traversal:\n");
    Inorder(root);
    printf("\nPreorder Traversal:\n");
    Preorder(root);
    printf("\nPostorder Traversal:\n");
    Postorder(root);
    return 0;
}

struct node *createChild(int parentValue, char *side) {
    int exists;
    printf("Does the %s child of %d exist? (1 = yes, 0 = no): ", side, parentValue);
    scanf("%d", &exists);
    if (exists == 0)
        return NULL;

    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    printf("Enter %s child of %d: ", side, parentValue);
    scanf("%d", &newNode->data);
    newNode->left = createChild(newNode->data, "left");
    newNode->right = createChild(newNode->data, "right");
    return newNode;
}

void Inorder(struct node *ptr) {
    if (ptr != NULL) {
        Inorder(ptr->left);
        printf("%d\t", ptr->data);
        Inorder(ptr->right);
    }
}
void Preorder(struct node *ptr) {
    if (ptr != NULL) {
        printf("%d\t", ptr->data);
        Preorder(ptr->left);
        Preorder(ptr->right);
    }
}
void Postorder(struct node *ptr) {
    if (ptr != NULL) {
        Postorder(ptr->left);
        Postorder(ptr->right);
        printf("%d\t", ptr->data);
    }
}

