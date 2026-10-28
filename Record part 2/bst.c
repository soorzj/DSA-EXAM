/***************************************************************
 * Program to implement Binary Search Tree in C using          *
 * and perform the basic tree functions                        *
 * Author: SOORAJ                                              *
 * Date: 17-8-26                                               *
 * Version: 5                                                  *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

void deleteElement(struct node **root, int data);

void main(){
    int data=0;
    int choice=0;
    while(choice!=6){
        printf("1. Create BST\n");
        printf("2. Insert Element\n");
        printf("3. Delete Element\n");
        printf("4. Search for element\n");
        printf("5. Display the BST\n");
        printf("6. Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter The Root Node Element to start Binary Search Tree:\n");
                data=0;
                scanf("%d",&data);
                struct node *root = createBST(data);
                break;
            case 2:
                data=0;
                while(data>=0){
                    printf("Enter Element to insert to Binary Search Tree (-1 to stop):\n");
                    scanf("%d",&data);
                    insertBST(root,data);
                }
                break;
            case 3:
                printf("Enter The Element to delete:\n");
                data=0;
                scanf("%d",&data);
                deleteElement(&root,data);
                break;
            case 4:
                printf("Enter The Element to search:\n");
                data=0;
                scanf("%d",&data);
                int result=searchElement(root,data);
                printf((result==1)?"Element Found Successfully\n":"Element Not Found\n");
                break;
            case 5:
                printf("The Binary Search Tree is:\n");
                inorder(root);
                printf("\n");
                break;
            case 6:
                printf("Exiting the program\n");
                break;
            default:
                printf("Invalid Choice\n");
        }
    }
    

struct node *createBST(int rootdata) {
    struct node *newRoot = (struct node *)malloc(sizeof(struct node));
    newRoot->data = rootdata;
    newRoot->left = NULL;
    newRoot->right = NULL;
    return newRoot;
}

void insertBST(struct node *root, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    struct node *current = root;
    struct node *parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else if (data > current->data)
            current = current->right;
        else {
            printf("Duplicate value not allowed\n");
            free(newNode);
            return;
        }
    }
    if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
}

int searchElement(struct node *root, int data) {
    struct node *current = root;

    while (current != NULL) {
        if (data == current->data)
            return 1;
        else if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    return 0;
}

void deleteElement(struct node **root, int data) {
    struct node *current = *root;
    struct node *parent = NULL;

    while (current != NULL && current->data != data) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) {
        printf("Element Not Found\n");
        return;
    }

    if (current->left != NULL && current->right != NULL) {
        struct node *successorParent = current;
        struct node *successor = current->right;

        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        current->data = successor->data;
        parent = successorParent;
        current = successor;
    }

    struct node *child = current->left != NULL ? current->left : current->right;
    if (parent == NULL)
        *root = child;
    else if (parent->left == current)
        parent->left = child;
    else
        parent->right = child;

    free(current);
    printf("Element Deleted Successfully\n");
}
void inorder(struct node *rootNode) {
    if (rootNode == NULL)
        return;
    inorder(rootNode->left);
    printf("%d ", rootNode->data);
    inorder(rootNode->right);
}

